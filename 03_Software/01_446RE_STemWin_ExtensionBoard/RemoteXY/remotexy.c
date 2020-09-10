/* RemoteXY.h 
   A RemoteXY Library - Remote device control
   version 2.4.4   
   ===========================================================
   For use RemoteXY library visit website http://remotexy.com
   This website will help you use the library for configuring 
   a remote control from a smartphone or tablet.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
        
   Supported modes: 
   All boards:
    #define REMOTEXY_MODE__HARDSERIAL                 - direct data transfer via HARDSERIAL
    #define REMOTEXY_MODE__SOFTSERIAL                 - direct data transfer via SOFTSERIAL
    #define REMOTEXY_MODE__ETHERNET                   - data transfer using <ethernet.h> library and open server
    #define REMOTEXY_MODE__ETHERNET_CLOUD             - data transfer using <ethernet.h> library and cloud connection
    #define REMOTEXY_MODE__HARDSERIAL_ESP8266         - data transfer via HARDSERIAL using AT commands of ESP8266 and open server
    #define REMOTEXY_MODE__HARDSERIAL_ESP8266_POINT   - data transfer via HARDSERIAL using AT commands of ESP8266 and open access point with a server
    #define REMOTEXY_MODE__HARDSERIAL_ESP8266_CLOUD   - data transfer via HARDSERIAL using AT commands of ESP8266 and cloud connection
    #define REMOTEXY_MODE__SOFTSERIAL_ESP8266         - data transfer via SOFTSERIAL using AT commands of ESP8266 and open server
    #define REMOTEXY_MODE__SOFTSERIAL_ESP8266_POINT   - data transfer via SOFTSERIAL using AT commands of ESP8266 and open access point with a server
    #define REMOTEXY_MODE__SOFTSERIAL_ESP8266_CLOUD   - data transfer via SOFTSERIAL using AT commands of ESP8266 and cloud connection
    #define REMOTEXY_MODE__WIFI                       - data transfer using wifi.h library and open server
    
   Only ESP8266 boards:
    #define REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI           - data transfer using <esp8266wifi.h> library and open server
    #define REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI_POINT     - data transfer using <esp8266wifi.h> library and open access point with a server
    #define REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI_CLOUD     - data transfer using <esp8266wifi.h> library and cloud connection

   Only ESP32 boards:
    #define REMOTEXY_MODE__ESP32CORE_WIFI                    - data transfer using <wifi.h> library and open server
    #define REMOTEXY_MODE__ESP32CORE_WIFI_POINT              - data transfer using <wifi.h> library and open access point with a server
    #define REMOTEXY_MODE__ESP32CORE_WIFI_CLOUD              - data transfer using <wifi.h> library and cloud connection
    #define REMOTEXY_MODE__ESP32CORE_BLE                     - data transfer using <BLEdevice.h> library
    #define REMOTEXY_MODE__ESP32CORE_BLUETOOTH               - data transfer using <BluetoothSerial.h> library of classic bluetooth

   Parameters depending on the selected mode (for example):
    #define REMOTEXY_SERIAL Serial  // for Hardware Serial
    #define REMOTEXY_SERIAL_SPEED 115200 
    #define REMOTEXY_SERIAL_RX 2   // for Software Serial
    #define REMOTEXY_SERIAL_TX 3   // for Software Serial
    #define REMOTEXY_WIFI_SSID "RemoteXY"  
    #define REMOTEXY_WIFI_PASSWORD "1234567890" 
    #define REMOTEXY_ETHERNET_MAC "DE:AD:BE:EF:EF:ED"  // for Ethernet modules
    #define REMOTEXY_SERVER_PORT 6377 
    #define REMOTEXY_CLOUD_TOKEN "xxxx" // for Cloud
    #define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com" // for Cloud
    #define REMOTEXY_CLOUD_PORT 6376  // for Cloud
    #define REMOTEXY_ACCESS_PASSWORD "1" 

   Debug log info on 115200 (define before include this library):
    #define REMOTEXY__DEBUGLOGS Serial

   = Version history ========================================

   version 2.2.5   
     - support MPIDE;
   version 2.3.1    
     - Support the device access password;
     - Support the cloud server as beta test;
     - Fixed a bug where the length of variables more than 255;
     - Fixed a bug where ESP module reboot and device did not see it;
     - Fixed a bug where the connection was filed and the device 
         did not see it and reconnection is impossible 
   version 2.3.4  
     - Fixed a bug where the length of all input variables more than 256;
     - Fixed a bug where millis() overflow in 50 days;
     - Fixed some bugs;
   version 2.3.5  
     - Fixed some bugs;
   version 2.4.1
     - support ESP32 WiFi and BLE   
   version 2.4.2
     - Fixed some bugs;
   version 2.4.3
     - Fixed some bugs;
   version 2.4.4
     - Fixed ESP32 BLE bugs;
   version 2.4.5
     - support ESP32 classic Bluetooth   
     - Fixed some bugs;
   version 2.4.6
     - update input variables on a smartphone;
          
*/

#ifndef _REMOTEXY_H_
#define _REMOTEXY_H_

//#define REMOTEXY__DEBUGLOGS Serial
#define REMOTEXY__DEBUGLOGS_SPEED 115200


#if defined(REMOTEXY_MODE__HARDSERIAL) || defined(REMOTEXY_MODE__SERIAL) || defined(REMOTEXY_MODE__HC05_HARDSERIAL) 
  #define REMOTEXY_MOD__SERIAL
  #define REMOTEXY_PORT__HARDSERIAL
#elif defined(REMOTEXY_MODE__SOFTSERIAL) || defined(REMOTEXY_MODE__SOFTWARESERIAL) || defined(REMOTEXY_MODE__HC05_SOFTSERIAL)
  #define REMOTEXY_MOD__SERIAL
  #define REMOTEXY_PORT__SOFTSERIAL
#elif defined(REMOTEXY_MODE__HARDSERIAL_ESP8266_POINT) || defined(REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT) || defined(REMOTEXY_MODE__ESP8266POINT_HARDSERIAL)
  #define REMOTEXY_MOD__ESP8266
  #define REMOTEXY_WIFI__POINT
  #define REMOTEXY_PORT__HARDSERIAL
#elif defined(REMOTEXY_MODE__SOFTSERIAL_ESP8266_POINT) || defined(REMOTEXY_MODE__ESP8266_SOFTSERIAL_POINT) || defined(REMOTEXY_MODE__ESP8266POINT_SOFTSERIAL)
  #define REMOTEXY_MOD__ESP8266
  #define REMOTEXY_WIFI__POINT
  #define REMOTEXY_PORT__SOFTSERIAL
#elif defined(REMOTEXY_MODE__HARDSERIAL_ESP8266) || defined(REMOTEXY_MODE__ESP8266_HARDSERIAL)
  #define REMOTEXY_MOD__ESP8266
  #define REMOTEXY_PORT__HARDSERIAL
#elif defined(REMOTEXY_MODE__SOFTSERIAL_ESP8266) || defined(REMOTEXY_MODE__ESP8266_SOFTSERIAL)
  #define REMOTEXY_MOD__ESP8266
  #define REMOTEXY_PORT__SOFTSERIAL
#elif defined(REMOTEXY_MODE__HARDSERIAL_ESP8266_CLOUD) || defined(REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD)
  #define REMOTEXY_MOD__ESP8266_CLOUD
  #define REMOTEXY_PORT__HARDSERIAL
  #define REMOTEXY_CLOUD
#elif defined(REMOTEXY_MODE__SOFTSERIAL_ESP8266_CLOUD) || defined(REMOTEXY_MODE__ESP8266_SOFTSERIAL_CLOUD)
  #define REMOTEXY_MOD__ESP8266_CLOUD
  #define REMOTEXY_PORT__SOFTSERIAL
  #define REMOTEXY_CLOUD
#elif defined(REMOTEXY_MODE__ETHERNET) || defined(REMOTEXY_MODE__ETHERNET_LIB) || defined(REMOTEXY_MODE__W5100_SPI)
  #define REMOTEXY_MOD__ETHERNET
#elif defined(REMOTEXY_MODE__ETHERNET_CLOUD) || defined(REMOTEXY_MODE__ETHERNET_LIB_CLOUD)
  #define REMOTEXY_MOD__ETHERNET_CLOUD
  #define REMOTEXY_CLOUD
#elif defined(REMOTEXY_MODE__WIFI) || defined(REMOTEXY_MODE__WIFI_LIB)
  #define REMOTEXY_MOD__WIFI
#elif defined(REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI_POINT) || defined(REMOTEXY_MODE__ESP8266WIFI_LIB_POINT) || defined(REMOTEXY_MODE__ESP8266WIFIPOINT_LIB) 
  #define REMOTEXY_MOD__ESPCORE_WIFI
  #define REMOTEXY_WIFI__POINT
#elif defined(REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI) || defined(REMOTEXY_MODE__ESP8266WIFI_LIB) 
  #define REMOTEXY_MOD__ESPCORE_WIFI
#elif defined(REMOTEXY_MODE__ESP8266CORE_ESP8266WIFI_CLOUD) || defined(REMOTEXY_MODE__ESP8266WIFI_LIB_CLOUD)                
  #define REMOTEXY_MOD__ESPCORE_WIFI_CLOUD 
  #define REMOTEXY_CLOUD
#elif defined(REMOTEXY_MODE__ESP32CORE_WIFI_POINT)  
  #define REMOTEXY_MOD__ESPCORE_WIFI
  #define REMOTEXY_WIFI__POINT
#elif defined(REMOTEXY_MODE__ESP32CORE_WIFI) 
  #define REMOTEXY_MOD__ESPCORE_WIFI
#elif defined(REMOTEXY_MODE__ESP32CORE_WIFI_CLOUD)
  #define REMOTEXY_MOD__ESPCORE_WIFI_CLOUD
  #define REMOTEXY_CLOUD
#elif defined(REMOTEXY_MODE__ESP32CORE_BLE)
  #define REMOTEXY_MOD__ESP32CORE_BLE
//
#elif defined(REMOTEXY_MODE__ESP32CORE_BLUETOOTH)
  #define REMOTEXY_MOD__ESP32CORE_BLUETOOTH
#else
  #error RemoteXY mode does not defined or defined error: REMOTEXY_MODE__XXXXXXX 
#endif


#include <inttypes.h> 


/*
#if defined(REMOTEXY_PORT__HARDSERIAL) || defined(REMOTEXY__DEBUGLOGS)
  #include <HardwareSerial.h>
#endif 
*/


#if defined(REMOTEXY_MOD__SERIAL) 
  #include "modules/serial.h" 
#elif defined(REMOTEXY_MOD__ESP8266)
  #include "modules/esp8266.h" 
#elif defined(REMOTEXY_MOD__ESP8266_CLOUD)
  #include "modules/esp8266_cloud.h" 
#elif defined(REMOTEXY_MOD__ETHERNET)
  #include "modules/ethernet.h" 
#elif defined(REMOTEXY_MOD__ETHERNET_CLOUD)
  #include "modules/ethernet_cloud.h" 
#elif defined(REMOTEXY_MOD__WIFI)
  #include "modules/wifi.h" 
#elif defined(REMOTEXY_MOD__ESPCORE_WIFI)
  #include "modules/espcore_wifi.h" 
#elif defined(REMOTEXY_MOD__ESPCORE_WIFI_CLOUD)
  #include "modules/espcore_wifi_cloud.h" 
#elif defined(REMOTEXY_MOD__ESP32CORE_BLE)
  #include "modules/esp32core_ble.h" 
#elif defined(REMOTEXY_MOD__ESP32CORE_BLUETOOTH)
  #include "modules/esp32core_bluetooth.h" 
#endif 

#ifndef REMOTEXY_ACCESS_PASSWORD 
#define REMOTEXY_ACCESS_PASSWORD ""
#endif 

CRemoteXY *remotexy;   

#define RemoteXY_Handler() remotexy->handler ()
#define RemoteXY_CONF const PROGMEM RemoteXY_CONF_PROGMEM

//API
#define RemoteXY_isConnected() remotexy->isConnected ()
#define RemoteXY_sendInputVariables() remotexy->sendInputVariables ()
#define RemoteXY_didSendInputVariables() remotexy->didSendInputVariables ()


#endif //_REMOTEXY_H_
/**********************************************************************************************************/

#ifndef _REMOTEXY_MOD_ESP8266_H_
#define _REMOTEXY_MOD_ESP8266_H_



#define REMOTEXY_ESP8266_MAX_SEND_BYTES 2048
#define REMOTEXY_ESP8266_MODULETEST_TIMEOUT 30000

class CRemoteXY : public CRemoteXY_AT {

protected:
  char * wifiSsid;
  char * wifiPassword;
  uint16_t port;
  char connectCannel;
  uint16_t connectAvailable;
  uint16_t freeAvailable;

  uint16_t sendBytesAvailable;  
  uint16_t sendBytesLater;
  
  uint32_t moduleTestTimeout;

public:

#if defined(REMOTEXY_PORT__HARDSERIAL)
  CRemoteXY (const void * _conf, void * _var, const char * _accessPassword, HardwareSerial * _serial, long _serialSpeed, const char * _wifiSsid, const char * _wifiPassword, uint16_t _port) {
    initSerial (_serial, _serialSpeed);
#elif defined(REMOTEXY_PORT__SOFTSERIAL)
  CRemoteXY (const void * _conf, void * _var, const char * _accessPassword, uint8_t _serialRx, uint8_t _serialTx, long _serialSpeed, const char * _wifiSsid, const char * _wifiPassword, uint16_t _port) {
    initSerial (_serialRx, _serialTx, _serialSpeed);
#endif
    initAT ();
    wifiSsid = (char *) _wifiSsid;
    wifiPassword = (char *) _wifiPassword;
    port = _port;
    connectCannel=0;
    connectAvailable=0;
    freeAvailable=0;
    sendBytesAvailable=0;
    sendBytesLater=0;
    init (_conf, _var, _accessPassword);
    moduleTestTimeout = millis ();
  }


  protected:
  uint8_t initModule () {
    
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
     
    return setModule (); 
  }
  
  uint8_t setModule () {    
    char sport[6];    
    rxy_itos (port, sport);
    char stimeout[6];
    rxy_itos (REMOTEXY_SERVER_TIMEOUT/1000, stimeout); 
    
    connectCannel=0;
    connectAvailable=0;
    
    sendATCommand ("ATE0",0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0;   
#if defined(REMOTEXY_WIFI__POINT)
    sendATCommand ("AT+CWMODE=2",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;   
    sendATCommand ("AT+CWDHCP=0,1",0);
    if (!waitATAnswer (AT_ANSWER_OK, 2000)) return 0;    
    char crypt[2] = {*wifiPassword?'4':'0',0};
    sendATCommand ("AT+CWSAP=\"",wifiSsid,"\",\"",wifiPassword,"\",10,",crypt,0);
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
    moduleTestTimeout = millis ();
    return 1;
  }

  
    
  void handlerModule () {
       
    while (serial->available ()>0) {      
      if (connectAvailable) break;
      if (freeAvailable) {
        serial->read ();
        freeAvailable--;
      }
      else {     
        readATMessage ();
      }
      moduleTestTimeout = millis ();
    }
    
    
    if (millis() - moduleTestTimeout > REMOTEXY_ESP8266_MODULETEST_TIMEOUT) {
      moduleTestTimeout = millis ();
      if (testATecho ()==2) setModule ();
    }  
    
  }
 
  //override AT
  void readyAT () {
    setModule ();
  }

  //override AT
  void connectAT () {
    if (connectCannel==0) {
      connectCannel=*(params[0]);
      connectAvailable=0;
    }
  };
 
  //override AT
  void closedAT () {
    if (connectCannel==*(params[0])) connectCannel=0;
  }
  
  //override AT
  void inputDataAT () {
    uint16_t size;
    size=getATParamInt (1);
    if (connectCannel==*(params[0])) connectAvailable=size; 
    else freeAvailable = size;
  }
  
  
  void sendStart (uint16_t len) {
    char s[8];
    if (connectCannel) {
      sendBytesLater=0;
      if (len>REMOTEXY_ESP8266_MAX_SEND_BYTES) {
        sendBytesLater=len-REMOTEXY_ESP8266_MAX_SEND_BYTES;
        len=REMOTEXY_ESP8266_MAX_SEND_BYTES;
      }
      sendBytesAvailable=len;
      rxy_itos (len, s+2);
      *s=connectCannel;
      *(s+1)=',';      
      sendATCommand ("AT+CIPSEND=",s,0);
      if (!waitATAnswer (AT_ANSWER_GO, 1000)) sendBytesAvailable=0;
    }
  }
  
  void sendByte (uint8_t b) {
    if (sendBytesAvailable) {
      serial->write (b); 
#if defined(REMOTEXY__DEBUGLOGS)
        DEBUGLOGS_writeOutputHex (b);
#endif
      sendBytesAvailable--;
      if (!sendBytesAvailable) {
        waitATAnswer (AT_ANSWER_SEND_OK, 1000);      
        if (sendBytesLater) sendStart (sendBytesLater); 
      }
    }
  }
  
  
  uint8_t receiveByte () {
    uint8_t b;
    if (connectAvailable) {
      if (serial->available ()>0) {
        connectAvailable--;
        b = serial->read  ();
#if defined(REMOTEXY__DEBUGLOGS)
        DEBUGLOGS_writeInputHex (b);
#endif
        return b;
      }
    }  
    return 0;
  }
  
  uint8_t availableByte () {
    if (connectAvailable) {
      return serial->available ()>0;
    }
    return 0;
  }  


};




#if defined(REMOTEXY_PORT__HARDSERIAL)
  #define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, &REMOTEXY_SERIAL, REMOTEXY_SERIAL_SPEED, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#elif defined(REMOTEXY_PORT__SOFTSERIAL)
  #define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_SERIAL_RX, REMOTEXY_SERIAL_TX, REMOTEXY_SERIAL_SPEED, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#endif


#endif //_REMOTEXY_MOD_ESP8266_H_
/**********************************************************************************************************/
#ifndef _REMOTEXY_AT_H_
#define _REMOTEXY_AT_H_

#include <inttypes.h> 

#include <string.h>
#include <stdarg.h>



#define AT_BUFFER_STR_LENGTH 10

const char * AT_ANSWER_ERROR = "ERROR";
const char * AT_ANSWER_OK = "OK";
const char * AT_ANSWER_SEND_OK = "SEND OK";
const char * AT_MESSAGE_READY = "ready";
const char * AT_ANSWER_GO = ">";
const char * AT_MESSAGE_AT = "AT";
const char * AT_MESSAGE_CONNECT = "?,CONNECT";
const char * AT_MESSAGE_CLOSED = "?,CLOSED";
const char * AT_MESSAGE_CONNECT_FAIL = "?,CONNECT FAIL";
const char * AT_MESSAGE_IPD = "+IPD,?,*:";


class CRemoteXY_AT : public CRemoteXY_Serial {
  
  protected:
  char bufferAT[AT_BUFFER_STR_LENGTH+1];
  uint8_t bufferATPos;
  char * params[3];
  uint8_t paramsLength[3];      
  uint8_t haveEcho;
    
  protected:
  void initAT () {
    bufferATPos=0;
  }

  virtual void closedAT () {};
  virtual void connectAT () {};
  virtual void readyAT () {};
  virtual void inputDataAT () {};
 
  protected:  
  void sendATCommand (const char * command, ...) { 
   
    char *p = (char*) command;
    va_list argptr;
    while (serial->available () > 0) serial->read (); 
    va_start (argptr, command);
    while (p) {
      serial->write (p);
#if defined(REMOTEXY__DEBUGLOGS)
      DEBUGLOGS_writeOutput (p);
#endif
      p=va_arg(argptr,char*);
    }
    va_end(argptr);     
    serial->write ("\r\n");
  }    
  
  protected:  
  uint8_t waitATAnswer (const char * answer, uint16_t delay) {
    uint8_t b;
    uint32_t timeOut = millis();
  
    uint8_t k=0;
    while (millis() - timeOut <= delay) {
    
    
      if (serial->available ()>0) {
        b=serial->read  ();
        if (b==10) continue;
#if defined(REMOTEXY__DEBUGLOGS)
        if (b==13) DEBUGLOGS_writeInputNewString ();
        else DEBUGLOGS_writeInputChar (b);
#endif
        if (b==13) {
          bufferAT[k++]=0; 
          bufferATPos=0;
          k=0;
          if (strcmp (bufferAT,answer)==0) return 1;
          if (strcmp (bufferAT,AT_ANSWER_ERROR)==0) return 0;
          if (cmpBufferAT () ==  AT_MESSAGE_READY) return 0;       
          if (strcmp (bufferAT,AT_MESSAGE_AT)==0) haveEcho=1;
        }
        else {
          if (k<AT_BUFFER_STR_LENGTH) bufferAT[k++]=b;
          if (b=='>') {
            if (answer==AT_ANSWER_GO) return 1;
          }
        }
      }
    } 
    return 0;  
  }

  // echo test, returns
  //  0 - no answer
  //  1 - no echo
  //  2 - have echo
  protected:  
  uint8_t testATecho () { 
    haveEcho = 0;
    sendATCommand ("AT",0);
    if (!waitATAnswer (AT_ANSWER_OK, 1000)) return 0;
    return (haveEcho==0?1:2);
  }


  protected:
  void readATMessage () {
    uint8_t b;
    while (serial->available ()>0) {
      b=serial->read  ();
      if (b==10) continue;
#if defined(REMOTEXY__DEBUGLOGS)
      if (b==13) DEBUGLOGS_writeInputNewString ();
      else DEBUGLOGS_writeInputChar (b);
#endif
      if (b==13) {
        bufferAT[bufferATPos]=0;
        bufferATPos=0;
         if (!cmpBufferAT ()) return;
      }
      else {
        if (bufferATPos<AT_BUFFER_STR_LENGTH) bufferAT[bufferATPos++]=b;  
        if (b==':') {
          bufferAT[bufferATPos]=0;
          if (strcmpAT (bufferAT,AT_MESSAGE_IPD)==0) {
#if defined(REMOTEXY__DEBUGLOGS)
            DEBUGLOGS_writeInputNewString ();
#endif
            bufferATPos=0;
            inputDataAT ();
            return;
          } 
        }
      }    
    }
  }
  
  protected:
  const char * cmpBufferAT () {
    if (strcmpAT (bufferAT,AT_MESSAGE_CONNECT)==0) {connectAT (); return AT_MESSAGE_CONNECT;}
    if (strcmpAT (bufferAT,AT_MESSAGE_CLOSED)==0) {closedAT (); return AT_MESSAGE_CLOSED;}             
    if (strcmpAT (bufferAT,AT_MESSAGE_CONNECT_FAIL)==0) {closedAT (); return AT_MESSAGE_CONNECT_FAIL;}             
    if (strcmpAT (bufferAT,AT_MESSAGE_READY)==0) {readyAT (); return AT_MESSAGE_READY;}    
    return 0;           
  }  
  
  protected:
  uint8_t strcmpAT (char * str, const char * temp) {
    uint8_t k = 0;
    while (*temp) {
      if (!*str) return 1;
      switch (*temp) {
        case '?':
          params[k]=str;
          paramsLength[k]=1;
          temp++; 
          str++;   
          k++; 
          break;
        case '*':
          params[k]=str;
          paramsLength[k]=0; 
          temp++;
          while (*str!=*temp) {
            if (!*str++) return 1; 
            paramsLength[k]++;
          }
          k++;
          break;
        default: 
          if (*(str++)!=*(temp++)) return 1;
          break;
      }
    }
    if (*temp) return 1;
    return 0;
  }  
  
  protected:
  uint16_t getATParamInt (uint8_t k) {
    uint16_t res = 0;
    char * p=params[k];
    uint8_t i=paramsLength[k];
    while (i--) res = res*10+(*p++)-'0';
    return res;
  }  
   
};

#endif //_REMOTEXY_AT_H_
//
#ifndef _REMOTEXY_SERIAL_H_
#define _REMOTEXY_SERIAL_H_



class CRemoteXY_Serial : public CRemoteXY_API {

public:

#if defined(REMOTEXY_PORT__HARDSERIAL)
  HardwareSerial * serial;
  void initSerial (HardwareSerial * _serial, long _serialSpeed) {
    serial = _serial;
    serial->begin (_serialSpeed);
  }
#elif defined(REMOTEXY_PORT__SOFTSERIAL)
  #if defined(SoftwareSerial_h)
    SoftwareSerial * serial;
    void initSerial (uint8_t _serialRx, uint8_t _serialTx, long _serialSpeed) {
      serial = new SoftwareSerial (_serialRx, _serialTx);
      serial->begin (_serialSpeed);
    }
  #elif defined(SoftSerial_h)
    SoftSerial * serial;
    void initSerial (uint8_t _serialRx, uint8_t _serialTx, long _serialSpeed) {
      serial = new SoftSerial (_serialRx, _serialTx);
      serial->begin (_serialSpeed);
    }
  #endif
#endif
};

#endif //_REMOTEXY_SERIAL_H_
//
#ifndef _RXY_LIB_H_
#define _RXY_LIB_H_

#include <inttypes.h> 


char* rxy_itos (uint16_t i, char* s) {
  uint8_t len=0;
  char *p=s+5;
  while (i) {
    *p--=i%10+'0';
    i/=10;
    len++;
  }
  for (i=0; i<len; i++) *s++=*(++p);
  *s=0;
  return s;  
}

uint8_t rxy_xctoi (char c) {
  uint8_t b;
  if (c<='9') b=c-'0';
  else if (c<='f') b=c-'A'+10; 
  else b=c-'a'+10;
  return b&0x0f;
}

void rxy_getMacAddr (char* s, uint8_t* m) {
  uint8_t i, b;
  for (i=6; i>0; i--) {
    b=rxy_xctoi (*s++)<<4;
    b|=rxy_xctoi (*s++);
    *m++=b;
    s++;
  }    
}



#endif //_RXY_LIB_H_
//
#ifndef _REMOTEXY_API_H_
#define _REMOTEXY_API_H_

#include <inttypes.h> 
#include <stdlib.h>



#define REMOTEXY_PACKAGE_START_BYTE 0x55
#define REMOTEXY_PASSWORD_LENGTH_MAX 26
#define REMOTEXY_TIMEOUT 5000
#define REMOTEXY_SERVER_TIMEOUT 7000
#define REMOTEXY_CLOUD_RETRY_TIMEOUT 500
#define REMOTEXY_CLOUD_CONNECT_TIMEOUT 10000
#define REMOTEXY_CLOUD_RECONNECT_TIMEOUT 30000
#define REMOTEXY_CLOUD_ECHO_TIMEOUT 60000

// cloud states
#define REMOTEXY_CLOUD_STATE_STOP 0 
#define REMOTEXY_CLOUD_STATE_WAIT_RECONNECT 1 
#define REMOTEXY_CLOUD_STATE_WAIT_NEXT_TRY 2 
#define REMOTEXY_CLOUD_STATE_CONNECTION 3
#define REMOTEXY_CLOUD_STATE_REGISTRATION 6 
#define REMOTEXY_CLOUD_STATE_WORKING 7


class CRemoteXY_API {
  protected:
  uint8_t confVersion;
  uint8_t *conf;
  uint8_t *var;
  uint8_t *accessPassword;
  uint16_t outputLength;
  uint16_t inputLength;
  uint16_t confLength;
  uint8_t *connect_flag;
  uint8_t inputVarNeedSend;

  uint8_t *receiveBuffer;
  uint16_t receiveBufferLength;
  uint16_t receiveIndex;
  uint16_t receiveCRC;

  
  uint32_t wireTimeOut;
  
  uint8_t moduleRunning;
    
  protected:
  virtual uint8_t initModule () {return 1;};
  virtual void handlerModule () {};
  virtual void closeConnection () {};
  virtual void sendStart (uint16_t len) {};
  virtual void sendByte (uint8_t b) {};
  virtual uint8_t receiveByte () {return 0;};
  virtual uint8_t availableByte () {return 0;};  
  
  public:
  void init (const void * _conf, void * _var, const char * _accessPassword) {
    uint8_t i;
    uint8_t* p = (uint8_t*)_conf;
    uint8_t b = getConfByte (p++);
    if (b==0xff) {
      inputLength = getConfByte (p++);
      inputLength |= getConfByte (p++)<<8;
      outputLength = getConfByte (p++);
      outputLength |= getConfByte (p++)<<8;
    }
    else {
      inputLength = b;
      outputLength = getConfByte (p++);    
    }
    confLength = getConfByte (p++);
    confLength |= getConfByte (p++)<<8;
    conf = p;
    confVersion = getConfByte (p);
    var = (uint8_t*)_var;
    uint16_t varLength = outputLength+inputLength;
    connect_flag = var+varLength;
    *connect_flag = 0;   
        
    accessPassword = (uint8_t*)_accessPassword;

    receiveBufferLength=inputLength;
    if ((*accessPassword!=0)&&(receiveBufferLength<REMOTEXY_PASSWORD_LENGTH_MAX))
      receiveBufferLength = REMOTEXY_PASSWORD_LENGTH_MAX;
    receiveBufferLength +=6;  
    
    receiveBuffer = (uint8_t*)malloc (receiveBufferLength);             
    
    p = var;
    i = varLength;
    while (i--) *p++=0;   
    
    resetWire ();
 
#if defined(REMOTEXY__DEBUGLOGS)
    DEBUGLOGS_init ();
    DEBUGLOGS_write("RemoteXY started");
#endif
  
    moduleRunning = initModule ();
#if defined(REMOTEXY__DEBUGLOGS)
    if (!moduleRunning) {
      DEBUGLOGS_write ("Wire module not available, RemoteXY stoped");
    }    
#endif     
    
  }

  
  private:
  inline uint8_t getConfByte (uint8_t* p) {
    return pgm_read_byte_near (p);                                     
  }
  
  private:
  void resetWire () {
    receiveIndex=0; 
    receiveCRC=initCRC ();
    *connect_flag = 0; 
    inputVarNeedSend = 1;
    wireTimeOut= millis();
  }
  
      
  public:
  void handler () {
    uint8_t *p;
    uint16_t i;  
    uint8_t b;
    uint16_t packageLength;
    
    if (!moduleRunning) return;
    
    handlerModule ();
    
#if defined(REMOTEXY_CLOUD)  
    handlerCloud ();
#endif
    
    while (availableByte () > 0) {  
      b = receiveByte ();  
      
      if ((receiveIndex==0) && (b!=REMOTEXY_PACKAGE_START_BYTE)) continue;   
      receiveBuffer[receiveIndex++]=b;
      updateCRC (&receiveCRC, b);
      if (receiveIndex>receiveBufferLength) {       
        searchStartByte (1); //receiveBuffer overflow
      }
      while (true) {
        if (receiveIndex<6) break;
        packageLength = receiveBuffer[1]|(receiveBuffer[2]<<8);
        if (packageLength>receiveBufferLength) searchStartByte (1); // error
        else if (packageLength<6) searchStartByte (1); // error
        else if (packageLength==receiveIndex) {      
          if (receiveCRC==0) {
            if (handleReceivePackage ()) {
              receiveIndex=0;
              receiveCRC=initCRC ();
              break;
            }
          }
          searchStartByte (1); // error 
        }
        else if (packageLength<receiveIndex) {
          uint16_t crc = initCRC ();
          p = receiveBuffer;
          i=packageLength;
          while (i--) updateCRC (&crc, *(p++)); 
          if (crc==0) {
            if (handleReceivePackage ()) {
              searchStartByte (packageLength);
              continue;
            }
          }
          searchStartByte (1);        
        }
        else break;
      }
    }  
    
    if (millis() - wireTimeOut > REMOTEXY_TIMEOUT) {
      resetWire ();
    }      
  }
  
  private:
  uint16_t initCRC () {
    return 0xffff;
  }          
    
  private:
  void updateCRC (uint16_t *crc, uint8_t b) {
    *crc ^= b;
    for (uint8_t i=0; i<8; ++i) {
      if ((*crc) & 1) *crc = ((*crc) >> 1) ^ 0xA001;
      else *crc >>= 1;
    }
  } 
  
  private:  
  void sendByteUpdateCRC (uint8_t b, uint16_t *crc) {
    sendByte (b); 
    updateCRC (crc, b);
  }  

  private:  
  void sendPackage (uint8_t command, uint8_t *p, uint16_t length, uint8_t itConf) {
    uint16_t crc = initCRC ();
    uint16_t packageLength = length+6;
    sendStart (packageLength);
    sendByteUpdateCRC (REMOTEXY_PACKAGE_START_BYTE, &crc);
    sendByteUpdateCRC (packageLength, &crc);
    sendByteUpdateCRC (packageLength>>8, &crc);
    sendByteUpdateCRC (command, &crc);  
    uint8_t b;
    while (length--) {
      if (itConf) b=getConfByte (p++);
      else b=*p++;
      sendByteUpdateCRC (b, &crc);
    }
    sendByte (crc);  
    sendByte (crc>>8);
  }
  
  private:  
  void searchStartByte (uint16_t pos) {
    uint8_t *p, *kp;
    uint16_t i;
    uint16_t ri = receiveIndex;
    p=receiveBuffer+pos;
    receiveCRC=initCRC ();
    for (i=pos; i<ri; i++) {
      if (*p==REMOTEXY_PACKAGE_START_BYTE) {      
        kp=receiveBuffer;
        receiveIndex=receiveIndex-i;
        while (i++<ri) {
          updateCRC (&receiveCRC, *p);              
          *(kp++)=*(p++);
        }
        return;
      }
      p++;
    }        
    receiveIndex=0;
  }  
  
  uint8_t handleReceivePackage () {
    uint8_t command;
    uint16_t i;
    uint16_t length;
    uint8_t *p, *kp;
       
    length = receiveBuffer[1]|(receiveBuffer[2]>>8); 
    length-=6;
    command = receiveBuffer[3];
    switch (command) {  
      case 0x00:  
        uint8_t available;
        if (length==0) {
          if (*accessPassword==0) available=1;
          else available=0;
        }
        else {
          uint8_t ch;
          available = 1;
          p = receiveBuffer+4;
          kp = accessPassword; 
          while (true) {
            ch=*kp++;
            if (ch!=*p++) available=0;
            if (!ch) break;
          }                               
        } 
        if (available!=0) {
          sendPackage (command, conf, confLength,  1);
          *connect_flag = 1;
        }
        else {
          uint8_t buf[4];
          p = buf;
          kp = conf;         
          i=confVersion>=5?3:2;
          length = i+1;
          while (i--) *p++ = getConfByte(kp++);
          *p++ = 0xf0;
          sendPackage (command, buf, length,  0);
        }          
        break;   
      case 0x40:  
        inputVarNeedSend = 0;
        sendPackage (command, var, inputLength+outputLength, 0); 
        break;   
      case 0x80:  
        if ((length==inputLength) && (inputVarNeedSend==0)) {
          p=receiveBuffer+4;
          kp=var;
          i= inputLength;
          while (i--) *kp++=*p++;
        }
        sendPackage (command, 0, 0, 0);
        break;   
      case 0xC0:  
        if (inputVarNeedSend!=0) command |= 0x01;
        sendPackage (command, var+inputLength, outputLength, 0);
        break;   
#if defined(REMOTEXY_CLOUD)  
      case 0x10: // echo
        sendPackage (command, 0, 0, 0);
        break;   
      case 0x11:
        if (cloudState==REMOTEXY_CLOUD_STATE_REGISTRATION) {
          setCloudState (REMOTEXY_CLOUD_STATE_WORKING);
        }
        break;   
#endif //REMOTEXY_CLOUD       
      default:
        return 0; 
    }  
    
    wireTimeOut=millis();    
#if defined(REMOTEXY_CLOUD)  
    if (cloudState==REMOTEXY_CLOUD_STATE_WORKING) {
      cloudTimeOut=millis();
    }
#endif //REMOTEXY_CLOUD       
    return 1;
  }
  
  
///////////////////////////////////////////////////////////////////////////////
// PUBLIC DOCUMENTED FUNCTIONS
  
  public:
  uint8_t isConnected () {
    return *connect_flag;
  }
  
  // transmit the input vars to smartphone, while input variables are transmitted the output variables are not sent
  public:
  void sendInputVariables () {
    inputVarNeedSend = 1;
  }

  //check if input variables were sent, return 1 if sent
  public:
  uint8_t didSendInputVariables () {
    if (inputVarNeedSend==0) return 1;
    else return 0;
  }

///////////////////////////////////////////////////////////////////////////////
// CLOUD SUPPORT 


#if defined(REMOTEXY_CLOUD)  
  protected:
  char *cloudServer;
  uint16_t cloudPort;
  uint8_t cloudRegistPackage[38];
  uint8_t cloudState;   
  uint32_t cloudTimeOut;


  virtual int8_t connectServerCloud (char * _cloudServer, uint16_t _cloudPort) {return 0;};

  public:
  void initCloud (const char * _cloudServer, uint16_t _cloudPort, const char * _cloudToken) {
    cloudServer = (char *) _cloudServer;
    cloudPort = _cloudPort;
    
    uint8_t i;
    uint8_t *p = cloudRegistPackage;
    *p++ = getConfByte(conf+0);
    *p++ = 0;    
    for (i=0; i<32; i++) {
      if (*_cloudToken==0) *(p++)=0;
      else *(p++)=*(_cloudToken++);
    }
    uint16_t *len = (uint16_t*)p;
    *len = outputLength + inputLength;
    if (confLength>*len) *len = confLength;   
    *len += 6+1;    
    len = (uint16_t*)(p+2);     
    *len = receiveBufferLength;  
    
    cloudState = REMOTEXY_CLOUD_STATE_STOP;
  }
  
  public:
  void startCloudConnection () {
    if (cloudState<REMOTEXY_CLOUD_STATE_CONNECTION) {
      setCloudState (REMOTEXY_CLOUD_STATE_CONNECTION);
    }
  }  
  
  public:
  void stopCloud () {
    closeConnection ();
    resetWire ();
    if (cloudState<REMOTEXY_CLOUD_STATE_CONNECTION) return;
#if defined(REMOTEXY__DEBUGLOGS)
    DEBUGLOGS_write("Cloud server disconnected");
#endif
    setCloudState (REMOTEXY_CLOUD_STATE_WAIT_RECONNECT);
  }
  
  private:
  void setCloudState (uint8_t state) {
    cloudState = state;
    cloudTimeOut = millis(); 
#if defined(REMOTEXY__DEBUGLOGS)
    switch (state) {
      case REMOTEXY_CLOUD_STATE_WAIT_RECONNECT: 
        DEBUGLOGS_write("Waiting to reconnect to the cloud server");
        break;
      case REMOTEXY_CLOUD_STATE_WAIT_NEXT_TRY: 
        DEBUGLOGS_write("Waiting to next try to connect to the cloud server");
        break;
      case REMOTEXY_CLOUD_STATE_CONNECTION: 
        DEBUGLOGS_write("Started connecting to cloud server");
        break;
      case REMOTEXY_CLOUD_STATE_REGISTRATION: 
        DEBUGLOGS_write("Waiting for registration on cloud server");
        break;
      case REMOTEXY_CLOUD_STATE_WORKING: 
        DEBUGLOGS_write("Connect to the cloud server successfully");
        break;
      default:
        DEBUGLOGS_write("Unknown cloud state ");
        REMOTEXY__DEBUGLOGS.print(cloudState);
        break;
    }
#endif
  }
  
  private:
  void handlerCloud () {
    int8_t res;
    if (!moduleRunning) return;
    switch (cloudState) {
      
      case REMOTEXY_CLOUD_STATE_WAIT_RECONNECT:  
        if (millis() - cloudTimeOut > REMOTEXY_CLOUD_RECONNECT_TIMEOUT)
          setCloudState (REMOTEXY_CLOUD_STATE_CONNECTION);          
        break;
        
      case REMOTEXY_CLOUD_STATE_WAIT_NEXT_TRY:  
        if (millis() - cloudTimeOut > REMOTEXY_CLOUD_RETRY_TIMEOUT) 
          setCloudState (REMOTEXY_CLOUD_STATE_CONNECTION);            
        break;
        
      case REMOTEXY_CLOUD_STATE_CONNECTION:  
        res = connectServerCloud (cloudServer, cloudPort);
        if (res == 1) {          
          setCloudState (REMOTEXY_CLOUD_STATE_REGISTRATION);   
          sendPackage (0x11, cloudRegistPackage, 38, 0);
        }
        else if (res == 0) {
#if defined(REMOTEXY__DEBUGLOGS)
          DEBUGLOGS_write("Cloud server connection error");          
#endif         
          setCloudState (REMOTEXY_CLOUD_STATE_WAIT_RECONNECT); 
        }
        else {
          setCloudState (REMOTEXY_CLOUD_STATE_WAIT_NEXT_TRY); 
        }
        break;
        
      case REMOTEXY_CLOUD_STATE_REGISTRATION:  
        if (millis() - cloudTimeOut > REMOTEXY_CLOUD_CONNECT_TIMEOUT) 
          stopCloud ();
        break;
        
      case REMOTEXY_CLOUD_STATE_WORKING:  
        if (millis() - cloudTimeOut > REMOTEXY_CLOUD_ECHO_TIMEOUT) 
          stopCloud ();
        break;
    }
  } 
  
///////////////////////////////////////////////////////////////////////////////
// PUBLIC DOCUMENTED FUNCTIONS OF CLOUD
  
  public:
  uint8_t isCloudConnected () {
    return (cloudState==REMOTEXY_CLOUD_STATE_WORKING ? 1:0);
  }
  
  
#endif //REMOTEXY_CLOUD

///////////////////////////////////////////////////////////////////////////////
// DEBUG FUNCTIONS

#if defined(REMOTEXY__DEBUGLOGS)
  uint8_t debug_flags;
  uint8_t debug_hexcounter;
  
  public:
  void DEBUGLOGS_init () {
    debug_flags=0;
    REMOTEXY__DEBUGLOGS.begin (REMOTEXY__DEBUGLOGS_SPEED);
    REMOTEXY__DEBUGLOGS.println();
  }

  public:
  void DEBUGLOGS_writeTime () {
    uint32_t d = millis();
    char s[15];
    sprintf (s, "[%5ld.%03d] ",(long)(d/1000), (int)(d%1000));     
    REMOTEXY__DEBUGLOGS.println ();    
    REMOTEXY__DEBUGLOGS.print (s);
  }
  
  public:
  void DEBUGLOGS_write (const char *s) {
    debug_flags = 0;
    DEBUGLOGS_writeTime (); 
    REMOTEXY__DEBUGLOGS.print(s);
  }
  
  public:
  void DEBUGLOGS_writeInput (char *s) {
    if ((debug_flags & 0x01)==0) {
      DEBUGLOGS_writeTime ();
      REMOTEXY__DEBUGLOGS.print("<- ");
    }
    debug_flags = 0x01;   
    REMOTEXY__DEBUGLOGS.print(s);
  }

  public:
  void DEBUGLOGS_writeOutput (char *s) {
    if ((debug_flags & 0x02)==0) {
      DEBUGLOGS_writeTime ();
      REMOTEXY__DEBUGLOGS.print("-> ");
    }
    debug_flags = 0x02;   
    REMOTEXY__DEBUGLOGS.print(s);
  }

  public:
  void DEBUGLOGS_writeInputHex (uint8_t b) {
    if ((debug_flags & 0x01)==0) {
      DEBUGLOGS_writeTime ();
      REMOTEXY__DEBUGLOGS.print("<-");
      debug_hexcounter=0;
    }
    debug_flags = 0x01;   
    DEBUGLOGS_writeHex (b);
  }

  public:
  void DEBUGLOGS_writeOutputHex (uint8_t b) {
    if ((debug_flags & 0x02)==0) {
      DEBUGLOGS_writeTime ();
      REMOTEXY__DEBUGLOGS.print("->");
      debug_hexcounter=0;
    }
    debug_flags = 0x02;
    DEBUGLOGS_writeHex (b);
  }
  
  public:
  void DEBUGLOGS_writeInputChar (char s) {
    if ((debug_flags & 0x01)==0) {
      DEBUGLOGS_writeTime ();
      REMOTEXY__DEBUGLOGS.print("<- ");
    }
    debug_flags = 0x01;   
    REMOTEXY__DEBUGLOGS.print(s);
  }

  public:
  void DEBUGLOGS_writeInputNewString () {
    debug_flags = 0;
  }
  
  public:
  void DEBUGLOGS_writeHex (uint8_t b) {
    debug_hexcounter++;
    if (debug_hexcounter>16) {
      REMOTEXY__DEBUGLOGS.println();
      REMOTEXY__DEBUGLOGS.print("              ");
      debug_hexcounter=1;
    }
    REMOTEXY__DEBUGLOGS.print(' ');
    REMOTEXY__DEBUGLOGS.print(b>>4, HEX); 
    REMOTEXY__DEBUGLOGS.print(b&0x0f, HEX); 
    
    
    
  }  
  
#endif //REMOTEXY__DEBUGLOGS 
   
};

#endif //_REMOTEXY_API_H_

