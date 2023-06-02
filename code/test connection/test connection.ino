#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
//#include "FeatherShieldPinouts.h";



const char* ssid = "voiture";
const char* password = "voitures";
const char* serverIP = "192.168.4.1";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connecté au réseau Wi-Fi ");
  Serial.println(ssid);

  Serial.print("Adresse IP de l'ESP en mode station : ");
  Serial.println(WiFi.localIP());

  client.connect(serverIP, 80);
}

void loop() {
  if (client.connected()) {
    Serial.println("Client connected. Sending message...");
    Serial.println(client.connected());
    client.println("Hello, ESP !");
    delay(1000);
    
    while (client.available()) {
      String response = client.readStringUntil('\n');
      Serial.print("Réponse du serveur : ");
      Serial.println(response);
    }
  } else {
    Serial.println("Connexion perdue. Tentative de reconnexion...");
    client.connect(serverIP, 80);
  }
}
