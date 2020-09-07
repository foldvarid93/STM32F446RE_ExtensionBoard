#ifndef _REMOTEXY_MOD_ESP8266_H_
#define _REMOTEXY_MOD_ESP8266_H_

#include "RemoteXY_AT.h"
#include "RemoteXY.h"

#define REMOTEXY_ESP8266_MAX_SEND_BYTES 2048
#define REMOTEXY_ESP8266_MODULETEST_TIMEOUT 30000


/*class CRemoteXY : public CRemoteXY_AT {

protected:
  char * wifiSsid;
  char * wifiPassword;
  uint16_t port;
  char cremotexy.connectCannel;
  uint16_t cremotexy.connectAvailable;
  uint16_t cremotexy.freeAvailable;

  uint16_t sendBytesAvailable;  
  uint16_t sendBytesLater;
  
  uint32_t cremotexy.moduleTestTimeout;

public:*/


void CRemoteXY_Init (const void * _conf, void * _var, const char * _accessPassword, HardwareSerial * _serial, long _serialSpeed, const char * _wifiSsid, const char * _wifiPassword, uint16_t _port);


  //protected:
  uint8_t initModule (void);
  
  uint8_t setModule (void);

  
    
  void handlerModule (void);
 
  //override AT
  void readyAT (void);

  //override AT
  void connectAT (void);
 
  //override AT
  void closedAT (void);
  
  //override AT
  void inputDataAT (void);
  
  
  void sendStart (uint16_t len);
  
  void sendByte (uint8_t b);
  
  
  uint8_t receiveByte (void);
  
  uint8_t availableByte (void);




#if defined(REMOTEXY_PORT__HARDSERIAL)
 // #define RemoteXY_Init() remotexy = CRemoteXY_Init (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, &REMOTEXY_SERIAL, REMOTEXY_SERIAL_SPEED, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#elif defined(REMOTEXY_PORT__SOFTSERIAL)
  #define RemoteXY_Init() remotexy = new CRemoteXY (RemoteXY_CONF_PROGMEM, &RemoteXY, REMOTEXY_ACCESS_PASSWORD, REMOTEXY_SERIAL_RX, REMOTEXY_SERIAL_TX, REMOTEXY_SERIAL_SPEED, REMOTEXY_WIFI_SSID, REMOTEXY_WIFI_PASSWORD, REMOTEXY_SERVER_PORT)
#endif


#endif //_REMOTEXY_MOD_ESP8266_H_
