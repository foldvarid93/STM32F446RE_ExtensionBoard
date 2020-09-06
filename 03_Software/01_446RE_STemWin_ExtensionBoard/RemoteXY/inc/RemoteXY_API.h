#ifndef _REMOTEXY_API_H_
#define _REMOTEXY_API_H_

#include <inttypes.h> 
#include <stdlib.h>
#include "RemoteXY.h"


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
#define AT_BUFFER_STR_LENGTH 10

typedef struct CRemoteXY
{
	//esp8266.h
	  char * wifiSsid;
	  char * wifiPassword;
	  uint16_t port;
	  char connectCannel;
	  uint16_t connectAvailable;
	  uint16_t freeAvailable;

	  uint16_t sendBytesAvailable;
	  uint16_t sendBytesLater;

	  uint32_t moduleTestTimeout;
	  //RemoteXY_AT.h
	  char bufferAT[AT_BUFFER_STR_LENGTH+1];
	  uint8_t bufferATPos;
	  char * params[3];
	  uint8_t paramsLength[3];
	  uint8_t haveEcho;
	  //RemoteXY_API.h
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
} CRemoteXY;

void init (const void * _conf, void * _var, const char * _accessPassword);
void resetWire ();
void handler ();
uint16_t initCRC ();
void updateCRC (uint16_t *crc, uint8_t b);
void sendByteUpdateCRC (uint8_t b, uint16_t *crc);
void sendPackage (uint8_t command, uint8_t *p, uint16_t length, uint8_t itConf);
void searchStartByte (uint16_t pos);
uint8_t handleReceivePackage ();
uint8_t isConnected ();
void sendInputVariables ();
uint8_t didSendInputVariables ();


#endif //_REMOTEXY_API_H_

