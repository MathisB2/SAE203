#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <string>
#include "score.h"
extern Adafruit_SH1107 display;
extern int screenWidth, screenHeight;

Score::Score():Score(10){
}

Score::Score(int endAt){
  this->resetScore();
  this->endAt=endAt;
  this->displayPosition=0;
}

void Score::win(){
  this->self++;
}

void Score::fail(){
  this->ennemy++;
}

void Score::resetScore(){
  this->self=0;
  this->ennemy=0;
  this->displayPosition=0;
}


void Score::displayScore(){
  display.setCursor(0, screenWidth+2);
  display.setTextSize(1);
  
  if(this->self<10 && this->ennemy<10){
    display.print("Score: ");
  }  else if((this->self<10 && this->ennemy>=10) || (this->self>=10 && this->ennemy<10)){
    display.print("Score:");
  }else{
    std::string s = "Score Score  ";

    display.print(s.substr(this->displayPosition/50,4).c_str());
    display.print(":");

    this->displayPosition++;
    if(this->displayPosition>=350){
      this->displayPosition=0;
    }
  }

  display.print(this->self);
  display.print("-");
  display.println(this->ennemy);
}



bool Score::checkForEnd(){
  return (this->self>=this->endAt) || (this->ennemy>=this->endAt);
}




void Score::displayEndMenu(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
   display.println(" YOU");
  if(this->self>=this->endAt){
    display.println(" WON");
  }else{
    display.setCursor(8, 16);
    display.println("LOST");
  }
  display.setTextSize(1);
  display.setCursor(0, 60);
  display.println(" A-Restart\n");
  display.println(" B-Quit");

  this->displayScore();
}