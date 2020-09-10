#include "esp8266.h"


extern CRemoteXY cremotexy;


extern const char * AT_ANSWER_GO;


void CRemoteXY_Init (const void * _conf, void * _var, const char * _accessPassword, const char * _wifiSsid, const char * _wifiPassword, uint16_t _port)
{
    initSerial();//_serial, _serialSpeed);
    initAT ();
    cremotexy.wifiSsid = (char *) _wifiSsid;
    cremotexy.wifiPassword = (char *) _wifiPassword;
    cremotexy.port = _port;
    cremotexy.connectCannel=0;
    cremotexy.connectAvailable=0;
    cremotexy.freeAvailable=0;
    cremotexy.sendBytesAvailable=0;
    cremotexy.sendBytesLater=0;
    init (_conf, _var, _accessPassword);
    cremotexy.moduleTestTimeout = millis ();
}


  //protected:
  uint8_t initModule (void) {
    
#if defined(REMOTEXY__DEBUGLOGS)
    DEBUGLOGS_write ("Find ESP module...");
#endif     

    uint8_t tryCount=20;
    while (--tryCount>0) {
      
      sendATCommand ("AT",0);
      if (waitATAnswer (AT_ANSWER_OK, 1000)) break;
    }
    if (tryCount==0) {
#if defined(REMOTEXY__DEBUGLOGS)
      DEBUGLOGS_write ("ESP module not found");
#endif     
      return 0;
    }
    sendATCommand ("AT+RST",0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0; 
    if (!waitATAnswer (AT_MESSAGE_READY, 5000)) return 0;
     
    return setModule(void);
  }
  
  uint8_t setModule (void) {
    char sport[6];    
    rxy_itos (cremotexy.port, sport);
    char stimeout[6];
    rxy_itos (REMOTEXY_SERVER_TIMEOUT/1000, stimeout); 
    
    cremotexy.connectCannel=0;
    cremotexy.connectAvailable=0;
    
    sendATCommand ("ATE0",0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0;   
#if defined(REMOTEXY_WIFI__POINT)
    sendATCommand ("AT+CWMODE=2",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;   
    sendATCommand ("AT+CWDHCP=0,1",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;    
    char crypt[2] = {*cremotexy.wifiPassword?'4':'0',0};
    sendATCommand ("AT+CWSAP=\"",cremotexy.wifiSsid,"\",\"",cremotexy.wifiPassword,"\",10,",crypt,0);
    if (!waitATAnswer (AT_ANSWER_OK, 5000)) return 0;  
#else
    sendATCommand ("AT+CWMODE=1",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;   
    sendATCommand ("AT+CWQAP",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;   
    sendATCommand ("AT+CWDHCP=1,1",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;    
    sendATCommand ("AT+CWJAP=\"",wifiSsid,"\",\"",wifiPassword,"\"",0);
    if (!waitATAnswer (AT_ANSWER_OK, 30000)) return 0;  
#if defined(REMOTEXY__DEBUGLOGS)
    sendATCommand ("AT+CIPSTA?",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;  
#endif     
#endif  
    sendATCommand ("AT+CIPMODE=0",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;   
    sendATCommand ("AT+CIPMUX=1",0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0;
    sendATCommand ("AT+CIPSERVER=1,",sport,0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0; 
    sendATCommand ("AT+CIPSTO=",stimeout,0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0; 
    cremotexy.moduleTestTimeout = millis ();
    return 1;
  }

  
    
  void handlerModule (void) {
       
    while (serial->available ()>0) {      
      if (cremotexy.connectAvailable) break;
      if (cremotexy.freeAvailable) {

    	  HAL_StatusTypeDef HAL_UART_Receive(huart3, uint8_t *pData, uint16_t Size, uint32_t Timeout);//serial->read ();
        cremotexy.freeAvailable--;
      }
      else {     
        readATMessage ();
      }
      cremotexy.moduleTestTimeout = millis ();
    }
    
    
    if (millis() - cremotexy.moduleTestTimeout > REMOTEXY_ESP8266_MODULETEST_TIMEOUT) {
      cremotexy.moduleTestTimeout = millis ();
      if (testATecho ()==2) setModule ();
    }  
    
  }
 
  //override AT
  void readyAT (void) {
    setModule ();
  }

  //override AT
  void connectAT (void) {
    if (cremotexy.connectCannel==0) {
      cremotexy.connectCannel=*(cremotexy.params[0]);
      cremotexy.connectAvailable=0;
    }
  };
 
  //override AT
  void closedAT (void) {
    if (cremotexy.connectCannel==*(cremotexy.params[0])) cremotexy.connectCannel=0;
  }
  
  //override AT
  void inputDataAT (void) {
    uint16_t size;
    size=getATParamInt (1);
    if (cremotexy.connectCannel==*(cremotexy.params[0])) cremotexy.connectAvailable=size;
    else cremotexy.freeAvailable = size;
  }
  
  
  void sendStart (uint16_t len) {
    char s[8];
    if (cremotexy.connectCannel) {
    	cremotexy.sendBytesLater=0;
      if (len>REMOTEXY_ESP8266_MAX_SEND_BYTES) {
    	  cremotexy.sendBytesLater=len-REMOTEXY_ESP8266_MAX_SEND_BYTES;
        len=REMOTEXY_ESP8266_MAX_SEND_BYTES;
      }
      cremotexy.sendBytesAvailable=len;
      rxy_itos (len, s+2);
      *s=cremotexy.connectCannel;
      *(s+1)=',';      
      sendATCommand ("AT+CIPSEND=",s,0);
      if (!waitATAnswer (AT_ANSWER_GO, 1000)) cremotexy.sendBytesAvailable=0;
    }
  }
  
  void sendByte (uint8_t b) {
    if (cremotexy.sendBytesAvailable) {
      //serial->write (b);
#if defined(REMOTEXY__DEBUGLOGS)
        DEBUGLOGS_writeOutputHex (b);
#endif
        cremotexy.sendBytesAvailable--;
      if (!cremotexy.sendBytesAvailable) {
        waitATAnswer (AT_ANSWER_SEND_OK, 1000);      
        if (cremotexy.sendBytesLater) sendStart (cremotexy.sendBytesLater);
      }
    }
  }
  
  
  uint8_t receiveByte (void) {
    uint8_t b;
    if (cremotexy.connectAvailable) {
      if (serial->available ()>0) {
        cremotexy.connectAvailable--;
        b = serial->read  ();
#if defined(REMOTEXY__DEBUGLOGS)
        DEBUGLOGS_writeInputHex (b);
#endif
        return b;
      }
    }  
    return 0;
  }
  
  uint8_t availableByte (void) {
    if (cremotexy.connectAvailable) {
      return serial->available ()>0;
    }
    return 0;
  }  



#if defined(REMOTEXY_PORT__HARDSERIAL)
  #define RemoteXY_Init() CRemoteXY_Init (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#elif defined(REMOTEXY_PORT__SOFTSERIAL)
  #define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_SERIAL_RX, REMOTEXY_SERIAL_TX, REMOTEXY_SERIAL_SPEED, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#endif
