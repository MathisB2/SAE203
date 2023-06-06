#ifndef JOYSTICK_H
#define JOYSTICK_H


class Joystick {
private:
  int xCenter;
  int yCenter;
  int xRange;
  int yRange;
  float deadZone;
public:
  Joystick ();
  double readX(bool);
  double readY(bool);
  void resetX();
  void resetY();
  void reset();
  bool isClicked();
};



#endif  // JOYSTICK_H_H
