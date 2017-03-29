#include <ESP8266WebServer.h>
#include <EEPROM.h>

namespace control
{
int addr = 0;
int addr2 = 0;
ESP8266WebServer server ( 80 );


void setRelayStatus(int relay, int state) {
  digitalWrite (relay, state);
  if (relay == 5) {
    addr = addr;
  }
  if (relay == 4) {
    addr = addr2;
  }
  EEPROM.write(addr, digitalRead(relay));
}

int getRelayStatus(int relay) {
  if (relay == 5) {
    addr = addr;
  }
  if (relay == 4) {
    addr = addr2;
  }
  return EEPROM.read(addr);
}

void toggleRelay() {
  char temp[400];

  int state = server.arg("state").toInt();
  if ((state == 1) or (state == 0)) {
    int relay = server.arg("relay").toInt();
    if ((relay == 5) or (relay == 4)) {

      setRelayStatus(relay, state);
      snprintf ( temp, 400,
                 "<html>\
  <head>\
    <title>NodeMCU DHT11 Sensor and Relay Board</title>\
    <meta http-equiv='refresh' content='0; url=../'>\
    </head>\
  <body>\
  %d .</body>\
  </html>", 0);
      server.send ( 200, "text/html", temp );
    }

  }

}



}



