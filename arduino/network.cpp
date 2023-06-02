#include <WiFi.h>
#include "network.h"

Network::Network()
{}

void Network::connectTo(const char* ssid, const char* password, String serverIP)
{

}

void Network::createServer(const char* ssid, const char* password, int port)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());

  server = WiFiServer(80);
  server.begin();
}

String Network::getMessage()
{
  return client.readStringUntil('\r');
}

int Network::clientConnected(){
  if(!client)
    client = server.available();

  return client && client.connected() && client.available();
}