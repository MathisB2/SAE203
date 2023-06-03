#include "BluetoothSerial.h"
#include "FeatherShieldPinouts.h"
#include "network.h"
#include <string>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);





#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

#define SSID "pongServer"
#define PASSWORD "12345678"

Network n;
int gameStatus = 0;  //0=connection menu, 1=ready , 2=in game
String player = "A";




void switchPlayer() {  //function linked to an interruption on button A
  if (gameStatus <= 1) {
    if (player == "A") {
      player = "B";
    } else {
      player = "A";
    }
    gameStatus = 0;
  }
}


void changeGameStatus() {  //function linked to an interruption on button B
  if (gameStatus != 0) {
    gameStatus++;
    if (gameStatus >= 3) {
      gameStatus = 0;
    }
  }
}





void setup() {
  Serial.begin(115200);

  display.begin(0x3C, true);
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  display.setRotation(1);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);



  //Add interruption to button A to switch player
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  attachInterrupt(BUTTON_A, switchPlayer, FALLING);
  attachInterrupt(BUTTON_B, changeGameStatus, FALLING);
}

void loop() {
  if (gameStatus == 2) {  //in game
    if (n.clientConnected() && n.clientAvailable())
      Serial.print(n.getMessage());
    //ball.updatePosition()
    //ball.display();
    //bar.display();

  } else if (gameStatus == 0) {
    if (player == "A") {  //player A is the host
      n.createServer(SSID, PASSWORD, 80);
      if (n.clientConnected() && n.clientAvailable())
        Serial.print(n.getMessage());
      //gameStatus = 1;

    } else if (player == "B") {  //player B is the guest
      n.connectTo(SSID, PASSWORD, "192.168.4.1");
      n.sendMessage("test");
      //gameStatus = 1;
    }

  } else if (gameStatus == 1) {  //ready to start game
    delay(1000);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("READY");
  }
}
