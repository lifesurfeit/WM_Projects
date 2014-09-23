#include "ball.h"

ball::ball(float a, float b)
{
  x = a;
  y = b; 
}

void ball::move(float m, float n)
{
  x+=m;
  y+=n;
}

void ball::setPosition(float c, float d)
{
  x = c;
  y = d;
}
float ball::getXPosition(void){ return x;}
float ball::getYPosition(void){ return y;}
