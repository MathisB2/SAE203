#include "ball.h"

Ball::Ball()
    :position(Vector(screenX/2.0,screenY/2.0)), direction(Vector(.5,.5))
{}

Ball::Ball(string ballInfo)
    :position(Vector(0,0)), direction(Vector(.5,.5))
{

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
