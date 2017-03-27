#include <ESP8266WebServer.h>

namespace control
{

ESP8266WebServer server ( 80 );


void toggleRelay() {
  char temp[400];

  int state = server.arg("state").toInt();
  if ((state == 1) or (state == 0)) {
    int relay = server.arg("relay").toInt();
    if ((relay == 5) or (relay == 4)) {
      digitalWrite (relay, state);
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

