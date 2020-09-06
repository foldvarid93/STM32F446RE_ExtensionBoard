#ifndef _REMOTEXY_API_H_
#define _REMOTEXY_API_H_

#include <inttypes.h> 
#include <stdlib.h>
#include "RemoteXY.h"
#include "RemoteXY_API.h"


CRemoteXY cremotexy;

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
        
    cremotexy.accessPassword = (uint8_t*)_accessPassword;

    receiveBufferLength=inputLength;
    if ((*cremotexy.accessPassword!=0)&&(cremotexy.receiveBufferLength<REMOTEXY_PASSWORD_LENGTH_MAX))
    	cremotexy.receiveBufferLength = REMOTEXY_PASSWORD_LENGTH_MAX;
    cremotexy.receiveBufferLength +=6;
    
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

  
//  private:
  inline uint8_t getConfByte (uint8_t* p) {
    return pgm_read_byte_near (p);                                     
  }
  
//  private:
  void resetWire () {
    receiveIndex=0; 
    receiveCRC=initCRC ();
    *connect_flag = 0; 
    cremotexy.inputVarNeedSend = 1;
    wireTimeOut= millis();
  }
  
      
//  public:
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
      updateCRC(&receiveCRC, b);
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
  
//  private:
  uint16_t initCRC () {
    return 0xffff;
  }          
    
//  private:
  void updateCRC (uint16_t *crc, uint8_t b) {
    *crc ^= b;
    for (uint8_t i=0; i<8; ++i) {
      if ((*crc) & 1) *crc = ((*crc) >> 1) ^ 0xA001;
      else *crc >>= 1;
    }
  } 
  
//  private:
  void sendByteUpdateCRC (uint8_t b, uint16_t *crc) {
    sendByte (b); 
    updateCRC (crc, b);
  }  

//  private:
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
  
//  private:
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
  
//  public:
  uint8_t isConnected () {
    return *connect_flag;
  }
  
  // transmit the input vars to smartphone, while input variables are transmitted the output variables are not sent
//  public:
  void sendInputVariables () {
    inputVarNeedSend = 1;
  }

  //check if input variables were sent, return 1 if sent
//  public:
  uint8_t didSendInputVariables () {
    if (inputVarNeedSend==0) return 1;
    else return 0;
  }

   
//};

#endif //_REMOTEXY_API_H_

