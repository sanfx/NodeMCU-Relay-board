
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include "login.h"
#include "control.h"
#include "webpage.h"
#include <DHT.h>

#define DHTTYPE DHT11     // DHT 11
#define DHTPIN 14
DHT dht(DHTPIN, DHTTYPE);
const char* host = "nodemcu";


const int led = 13;
const int outputLed = 12;

void outputJson() {
  char temp[400];
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int tf = dht.readTemperature(true);
  snprintf ( temp, 400,
             "{\"nodemcu\" : [{\"location\" : \"phillaur\" ,\
\"temperatureInC\" :%2d ,\
\"temperatureInF\" :%2d ,\
\"humidity\":%2d,\
\"relay1\":%d,\
\"relay2\":%d\
}]}",
             t, tf, h, control::getRelayStatus(5), control::getRelayStatus(4));
  control::server.send ( 200, "text/json", temp );
}

void handleRoot() {
  const int nsize = 3000;
  char temp[nsize];
  delay(200);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  snprintf ( temp, nsize,
             
  "%s\n\
  <button id=\'btn1\' onclick=\"turnOnRelay(this, \'5\')\" class=\'button button3\'>Turn %s Light</button><br>\n\
  <button id=\'btn2\' onclick=\"turnOnRelay(this, \'4\')\" class=\'button button3\'>Turn %s Fan</button>\n\t\
  </\div></body>\n\
</html>",webpage::html,

(control::getRelayStatus(5) ? "Off" : "On"),
(control::getRelayStatus(4) ? "Off" : "On"));
  control::server.send ( 200, "text/html", temp );
}

void handleNotFound() {
  digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += control::server.uri();
  message += "\nMethod: ";
  message += ( control::server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += control::server.args();
  message += "\n";

  for ( uint8_t i = 0; i < control::server.args(); i++ ) {
    message += " " + control::server.argName ( i ) + ": " + control::server.arg ( i ) + "\n";
  }

  control::server.send ( 404, "text/plain", message );
  digitalWrite ( led, 0 );
}

void setup ( void ) {
  pinMode ( led, OUTPUT );
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(outputLed, OUTPUT);
  digitalWrite ( led, 0 );
  Serial.begin ( 9600 );
  // config static IP
  IPAddress ip(192, 168, 1, 88);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(192, 168, 1, 1);
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(login::ssid, login::password);
  Serial.println ( "" );
  EEPROM.begin(512);

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( login::ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( host ) ) {
    Serial.println ( "MDNS responder started" );
  }
  MDNS.addService("http", "tcp", 80);
  control::server.on ( "/", handleRoot );
  control::server.on("/json", outputJson);
  control::server.on("/control", control::toggleRelay);
  control::server.onNotFound (handleNotFound);
  control::server.begin();
  Serial.println (F("HTTP server started"));
  // get relay state from the last saved in EEPROM
  digitalWrite(5, control::getRelayStatus(5));
  digitalWrite(4, control::getRelayStatus(4));
}

void loop ( void ) {
  control::server.handleClient();
  //  Blynk.run();
}

