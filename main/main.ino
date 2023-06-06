#include "BluetoothSerial.h"
#include "FeatherShieldPinouts.h"
#include "network.h"
#include "point.h"
#include "bar.h"
#include "ball.h"
#include "score.h"
#include <string>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <vector>
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
#include <iostream>
using namespace std;

#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

#define SSID "pongServer"
#define PASSWORD "12345678"

Network n;

int gameStatus = 0;  //0=connection menu, 1=waiting, 2=ready, 3=in game, 4=end menu
String player = "A";
int joystickMiddle;
int joystickRange = 900;
int joystickSensivity = 350;  //value in % (default: 350)

int screenWidth = 119;
int screenHeight = 64;

Bar playerBar(20, 5, 50, false);
Bar topBar(screenHeight * 2, 0, 0);
Bar bottomBar(screenHeight * 2, 0, screenWidth);
Bar goalBar(screenWidth, 0, 0, false, false, true);
Bar portalBar(screenWidth, screenHeight, 0, false, false, true);
Ball* b = nullptr;

Score score(10);
String m;  //String used to read messages (need trim)

void IRAM_ATTR buttonB() {  //function linked to an interruption on button B
  if (gameStatus <= 2) {    //switchPlayer
    if (player == "A") {
      player = "B";
    } else {
      player = "A";
    }
    gameStatus = 0;
    display.setRotation(1);
  }


  else if (gameStatus >= 3) {  //quit the game
    gameStatus = 0;
    display.setRotation(1);
  }
}


void startGame() {
  if (b != nullptr)
    delete b;
  b = new Ball());
  display.setRotation(0);

  score.resetScore();
  playerBar.resetLocation();
  n.sendMessage("start");
  gameStatus = 3;  //start the game
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

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  //pinMode(BUTTON_C, INPUT_PULLUP);


  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  //attachInterrupt(BUTTON_A, buttonA, FALLING);
  attachInterrupt(BUTTON_B, buttonB, FALLING);
  joystickMiddle = analogRead(A4);
}

unsigned long currentTime = millis();

void loop() {
  double delta = (double)(millis() - currentTime) / 1000;
  currentTime = millis();


  if (gameStatus == 0) {  //starting connection ---------------------------------------------------------------
    if (player == "A") {  //player A is the host
      n.createServer(SSID, PASSWORD, 80);
      gameStatus = 1;

    } else if (player == "B") {  //player B is the guest
      n.connectTo(SSID, PASSWORD, "192.168.4.1");
      gameStatus = 1;
    }
  }

  else if (gameStatus == 1) {  //waiting for ready message ----------------------------------------------------
    if (n.clientConnected()) {
      if (player == "A") {
        //wait for ready message
        if (n.clientAvailable() > 0) {
          m = n.getMessage();
          Serial.print("Message reçu : ");
          Serial.println(m);
          m.trim();
          if (m.equals("ready")) {
            gameStatus = 2;
            Serial.println("bien recu");
          }
        }
      }

      if (player == "B") {
        //send ready message
        n.sendMessage("ready");
        gameStatus = 2;
      }
    }
  }



  else if (n.clientConnected() && gameStatus > 1) {
    if (gameStatus == 2) {  //start interface (A to start) -----------------------------------------------------
      display.clearDisplay();
      display.setCursor(0, 0);

      if (player == "A") {
        display.println("PLAYER A : host\n\n");
      } else if (player == "B") {
        display.println("PLAYER B : guest\n\n");
      }

      display.println("Ready");
      display.print("Press A to start");
      display.display();

      //wait for start message
      if (n.clientAvailable() > 0) {
        m = n.getMessage();
        m.trim();
        if (m.equals("start")) {
          gameStatus = 3;
        }
      }
      if (digitalRead(BUTTON_A) == 0) {
        //made a function to reset all necessary variables to restart a game (need to be used in 2 times)
        startGame();
      }
    }


    if (gameStatus == 3) {  //in game -----------------------------------------------------------------------------

      if (n.clientAvailable()) {
        m = n.getMessage();
        m.trim();
        if (m.equals("fail")) {
          score.win();
          if (score.checkForEnd()) {
            gameStatus = 4;
          }
        } else if (m.substring(0, 4).equals("Ball")) {
          b = new Ball());
        }
      }

      display.clearDisplay();

      if (b != nullptr) {
        b->move(delta);
        b->draw();
        Vector& ballDirection = b->getDirection();

        if (b->inPortal && ballDirection.getX() < 0) {  //if the ball comes from the other screen
          b->inPortal = false;
        }
        if (b->inPortal && !portalBar.isCollidedBy(*b) && ballDirection.getX() > 0) {  //if the ball get out of the screen
          delete (b);
          b = nullptr;
        } else if (!b->inPortal && portalBar.isCollidedBy(*b) && ballDirection.getX() > 0) {  //if the edge of the ball starts touching the screen limit
          n.sendMessage(b->toString());
          b->inPortal = true;
        } else if (goalBar.isCollidedBy(*b)) {
          n.sendMessage("fail");
          score.fail();
          if (score.checkForEnd()) {
            gameStatus = 4;
          }

          delete (b);
          b = nullptr;
        }
      }

      playerBar.updateLocation(delta);
      playerBar.drawBar();
      topBar.drawBar();
      bottomBar.drawBar();
      goalBar.drawBar();

      score.displayScore();

      display.display();
    }

    if (gameStatus == 4) {  //end menu with restart and quit options --------------------------------------------------
      score.displayEndMenu();
      display.display();
    }

  } else {  //connection lost
    display.clearDisplay();
    display.setRotation(1);
    display.setTextSize(1);
    display.setCursor(12, 28);
    display.println("Connection lost !");
    display.display();
    delay(1500);
    gameStatus = 0;
  }
}