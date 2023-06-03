#include <WiFi.h>
#include "network.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
extern Adafruit_SH1107 display;
extern int gameStatus;

Network::Network() {}

void Network::connectTo(const char* ssid, const char* password, const char* serverIP) {
  if (WiFi.getMode() != WIFI_STA) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PLAYER B : guest\n");
    display.println("Connecting...");
    display.display();

    Serial.print("Connecting");
    client.connect(serverIP, 80);
  }


  /*
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }*/

  if (WiFi.status() == WL_CONNECTED) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PLAYER B : guest\n");
    display.println("Connected");
    display.print("IP : ");
    display.println(WiFi.localIP());
    display.display();

    /*
    Serial.print("Adresse IP de l'ESP en mode station : ");
    Serial.println(WiFi.localIP());*/
  }

  
}

void Network::createServer(const char* ssid, const char* password, int port) {

  if (WiFi.getMode() != WIFI_AP) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PLAYER A : host\n");
    display.println("Creating server...");
    display.display();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);


    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PLAYER A : host\n");
    display.println("Server created");
    display.print("IP : ");
    display.println(WiFi.softAPIP());
    display.display();

    Serial.print("AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());

    server = WiFiServer(80);
    server.begin();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PLAYER A : host\n");
    display.println("Server created");
    display.print("IP : ");
    display.println(WiFi.softAPIP());
    display.println();
    display.println("Waiting for player B");
    display.display();
  }
}

void Network::sendMessage(String message) {
  client.println(message);
}

String Network::getMessage() {
  return client.readStringUntil('\n');
}

int Network::clientConnected() {
  if (!client)
    client = server.available();

  return client.connected();
}

int Network::clientAvailable() {
  return client.available();
}