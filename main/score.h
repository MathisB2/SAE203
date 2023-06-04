#ifndef SCORE_H
#define SCORE_H


class Score {
private:
  int self;
  int ennemy;
  int endAt;
  int displayPosition;
public:
  Score();
  Score(int);

  void win();
  void fail();
  void resetScore();

  void displayScore();
  void displayEndMenu();
  bool checkForEnd();

  
};



#endif  // SCORE_H
