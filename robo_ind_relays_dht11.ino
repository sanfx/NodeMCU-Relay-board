
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include "login.h"
#include "control.h"
#include <DHT.h>

char noipServer[] = "https://dynupdate.no-ip.com";

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
             "{'nodemcu' : [{'location' : 'phillaur' ,\
'temperatureInC' :%2d ,\
'temperatureInF' :%2d ,\
'humidity':%2d,\
'relay1':%d,\
'relay2':%d\
}]}",
             t, tf, h, digitalRead(5), digitalRead(4));
  control::server.send ( 200, "text/json", temp );
}


void handleRoot() {
  digitalWrite ( led, 1 );

  char temp[800];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  snprintf ( temp, 800,
             "<html>\
  <head>\
    <meta http-equiv='refresh' content='25'/>\
    <title>NodeMCU DHT11 Sensor \and Relay Board</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      li { margin: 10px 0;}\
    </style>\
  </head>\
  <body>\
  <h1>Hello from NodeMCU!</h1>\
  <p>Temperature: %02d &#8451;<br>\
  Humidity: %2d %<br></p><ol>\
  <li><a href='/control?relay=5&state=%d'>Turn Relay 1 %s</a>\
  <li><a href='/control?relay=4&state=%d'>Turn Relay 2 %s</a></ol>\
    <p> Uptime: %02d:%02d:%02d </p>\
  </body>\
</html>",
             t,
             h,
             !digitalRead(5), (digitalRead(5) ? "Off" : "On"),
             !digitalRead(4), (digitalRead(4) ? "Off" : "On"),
             hr, min % 60, sec % 60
           );
  control::server.send ( 200, "text/html", temp );
  digitalWrite ( led, 0 );
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
  WiFi.begin(login::ssid, login::password);
  Serial.println ( "" );
  //Blynk.begin(auth, ssid, password);
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

  control::server.on ( "/inline", []() {
    control::server.send ( 200, "text/plain", "this works as well" );
  } );
  control::server.on("/json", outputJson);
  control::server.on("/control", control::toggleRelay);
  control::server.onNotFound ( handleNotFound );
  control::server.begin();
  Serial.println ( "HTTP server started" );
}



void loop ( void ) {
  control::server.handleClient();
  //  Blynk.run();
}

