#ifndef _REMOTEXY_AT_H_
#define _REMOTEXY_AT_H_

#include <inttypes.h> 
#include <string.h>
#include <stdarg.h>
#include "RemoteXY_Serial.h"


  void initAT (void);

  void sendATCommand (const char * command, ...);
  
  uint8_t waitATAnswer (const char * answer, uint16_t delay);

  uint8_t testATecho (void);

  void readATMessage (void);
  
  const char * cmpBufferAT (void);
  
  uint8_t strcmpAT (char * str, const char * temp);
  
  uint16_t getATParamInt (uint8_t k);

#endif //_REMOTEXY_AT_H_
