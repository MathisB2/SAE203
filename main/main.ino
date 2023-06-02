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
bool gameStarted=false;
String player="A";




void switchPlayer(){ //function linked to an interruption on button A
  if(player=="A"){
    player="B";
  }
  else{
    player="A";
  }
}


void switchGameState(){ //function linked to an interruption on button B
  gameStarted=!gameStarted;
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
  attachInterrupt(BUTTON_B, switchGameState, FALLING);


}

void loop() {
  if(gameStarted){
    if(n.clientConnected() && n.clientAvailable())
    Serial.print(n.getMessage());
    //ball.updatePosition()
  }else{
    if(player=="A"){ //player A is the host
      n.createServer(SSID, PASSWORD, 80);
      display.println("PLAYER");
      gameStarted=true;
    }
    else if(player=="B"){ //player B is the guest
      n.connectTo(SSID, PASSWORD, "192.168.4.1");
      gameStarted=true;
    }
  }
  
}
