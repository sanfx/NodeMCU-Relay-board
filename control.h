#include <ESP8266WebServer.h>
#include <EEPROM.h>

namespace control
{

ESP8266WebServer server ( 80 );

void setRelayStatus(int relay, int state) {
  digitalWrite (relay, state);
  if (relay == 5) {
    EEPROM.write(0, state);
  }
  if (relay == 4) {
    EEPROM.write(1, state);
  }
  EEPROM.commit();
  delay(100);
}

int getRelayStatus(int relay) {
  if (relay == 5) {
    return EEPROM.read(0);
  }
  if (relay == 4) {
    return EEPROM.read(1);
  }
}

void toggleRelay() {
  char temp[400];
  int relay = server.arg("relay").toInt();
  int state = !digitalRead(relay);
  if ((state == 1) or (state == 0)) {
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



