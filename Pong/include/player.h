#pragma once
class player
{
  protected:
    int x;
    float y;
  public:
    player(int a, float b);
    void move(float z);
    int getXPosition(void);
    float getYPosition(void);
    void setYPosition(float m);
};


