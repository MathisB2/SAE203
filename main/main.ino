#include "BluetoothSerial.h"
#include "FeatherShieldPinouts.h"
#include "network.h"
#include "point.h"
#include "bar.h"
#include "score.h"
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
int gameStatus = 2;  //0=connection menu, 1=ready, 2=in game, 3=end menu
String player = "A";
int joystickMiddle;
int joystickRange = 900;
int joystickSensivity = 350;  //value in % (default: 350)

int screenWidth = 119;
int screenHeight = 64;


Bar playerBar(20, 5, 50, false);
Bar topBar(screenHeight, 0, 0);
Bar bottomBar(screenHeight, 0, screenWidth);
Bar goalBar(screenWidth, 0, 0,false,false,true);

Score score(10);



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
  if (gameStatus == 1) {
    gameStatus++;
  }
  if (gameStatus >= 3) {
    gameStatus = 0;
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

  playerBar.resetLocation();


  //Add interruption to button A to switch player
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  attachInterrupt(BUTTON_A, switchPlayer, FALLING);
  attachInterrupt(BUTTON_B, changeGameStatus, FALLING);
  joystickMiddle = analogRead(A0);
}



void loop() {
  if (gameStatus == 2) {  //in game


  //if(n.clientConnected()){

    
    display.clearDisplay();
    playerBar.updateLocation();
    playerBar.drawBar();
    topBar.drawBar();
    bottomBar.drawBar();
    goalBar.drawBar();

    score.displayScore();

    display.display();


      if (n.clientAvailable()){

        Serial.print(n.getMessage());
        if(n.getMessage()=="fail"){
          score.win();
          if(score.checkForEnd()){
            gameStatus=3;
          }
        }

        
      }

   /*   
    ball.updatePosition()
    ball.display();
    bar.display();



  }else{
    Serial.pintln("Connection lost");
    gameStaus=0;
  }*/


  } else if (gameStatus == 0) {
    if (player == "A") {  //player A is the host
      n.createServer(SSID, PASSWORD, 80);
      gameStatus = 1;

    } else if (player == "B") {  //player B is the guest
      n.connectTo(SSID, PASSWORD, "192.168.4.1");
      //n.sendMessage("test");
      gameStatus = 1;
    }

  } else if (gameStatus == 1) {  //ready to start game
    if ((player == "A" && n.getClientNumber() == 1)) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("PLAYER A : host\n\n");
      display.println("Ready");
      display.print("Press B to start");
      display.display();
    }

    if (player == "B") {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("PLAYER B : guest\n\n");
      display.println("Ready");
      display.print("Press B to start");
      display.display();
    }



    /*
    delay(100);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("READY");
    display.display();

    Serial.print(player);
    Serial.print(" : ");
    Serial.println(n.getClientNumber());

    /*

    if(n.clientConnected() && n.clientAvailable() && player=="A"){
      Serial.print("A : Message recivied : ");
      Serial.println(n.getMessage());
    }

    if(n.clientConnected() && player=="B"){
      Serial.println("B : Sending message");
      n.sendMessage("BtoA");
    }


    delay(5000);
    */
  }
}
