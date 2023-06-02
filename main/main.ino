#include "BluetoothSerial.h"
#include "FeatherShieldPinouts.h"
#include "network.h"

Network n;
void setup() {
  Serial.begin(115200);
  n.createServer("voiture", "voitures", 80);
}

void loop() {
  if(n.clientConnected())
    Serial.print(n.getMessage());
}
