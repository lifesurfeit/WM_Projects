#include "player.h"

player::player (int a, float b){
   x = a;
   y = b;
}

void player::move (float z){
  //if(y<=575.0 && y >=0.0)
    y+=z;
}

int player::getXPosition(void){
   return x;
}

float player::getYPosition(void){
  return y;
}

void player::setYPosition(float m){
  y = m;
}