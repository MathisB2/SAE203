#include "ball.h"

Ball::Ball()
    :position(Vector(screenX/2.0,screenY/2.0)), direction(Vector(.5,.5)), speed(5), radius(2)
{}

Ball::Ball(String ballInfo)
    :position(Vector(0,0)), direction(Vector(.5,.5))
{
  //ballInfo.substring()
}

String Ball::toString()
{
  String posStr = String(position.getX())+";"+String(position.getY());
  String dirStr = String(direction.getX())+";"+String(direction.getY());

  return "Ball;"+posStr+";"+dirStr+";"+speed+";"+radius;
}

void Ball::move(double delta)
{
    position += direction*speed*delta;

    if(position.getY() <= 0 || position.getY() >= screenY)
    {
        direction.setY(direction.getY()*-1);
    }
}

bool Ball::changeScreen()
{
    return position.getX() >= screenX;
}

bool Ball::loose()
{
    return position.getX() <= 0;
}