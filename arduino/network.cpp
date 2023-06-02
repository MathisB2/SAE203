#include <WiFi.h>
#include "network.h"

Network::Network() {}

void Network::connectTo(const char* ssid, const char* password, const char* serverIP) {
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Adresse IP de l'ESP en mode station : ");
  Serial.println(WiFi.localIP());

  client.connect(serverIP, 80);
}

void Network::createServer(const char* ssid, const char* password, int port) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());

  server = WiFiServer(80);
  server.begin();
}

void Network::sendMessage(String message){
    client.println(message);
}

String Network::getMessage() {
  return client.readStringUntil('\n');
}

int Network::clientConnected() {
  if (!client)
    client = server.available();

  return client && client.connected() && client.available();
}