#pragma once
class ball
{
  float x, y;
public:
  ball(float a, float b);
  void move(float m, float n);
  void setPosition(float c, float d);
  float getXPosition(void);
  float getYPosition(void);
};
