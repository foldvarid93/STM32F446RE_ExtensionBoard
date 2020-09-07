#ifndef _REMOTEXY_AT_H_
#define _REMOTEXY_AT_H_

#include <inttypes.h> 
#include <string.h>
#include <stdarg.h>
#include "RemoteXY_Serial.h"

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


/*class CRemoteXY_AT : public CRemoteXY_Serial {
  
  protected:
  char bufferAT[AT_BUFFER_STR_LENGTH+1];
  uint8_t cremotexy.bufferATPos;
  char * cremotexy.params[3];
  uint8_t paramsLength[3];      
  uint8_t cremotexy.haveEcho;
    
  protected:*/
  void initAT (void);

/*  virtual void closedAT () {};
  virtual void connectAT () {};
  virtual void readyAT () {};
  virtual void inputDataAT () {};*/
 
//  protected:
  void sendATCommand (const char * command, ...);
  
//  protected:
  uint8_t waitATAnswer (const char * answer, uint16_t delay);

  // echo test, returns
  //  0 - no answer
  //  1 - no echo
  //  2 - have echo
//  protected:
  uint8_t testATecho (void);


//  protected:
  void readATMessage (void);
  
//  protected:
  const char * cmpBufferAT (void);
  
//  protected:
  uint8_t strcmpAT (char * str, const char * temp);
  
//  protected:
  uint16_t getATParamInt (uint8_t k);
   
//};

#endif //_REMOTEXY_AT_H_
