#include "Logic.h"
#include <cmath>

Logic::Logic(ball &x, player &y, player &z)
{
  const int width = 800;
  const int height = 600;
  const int borderSize = 12;
  
  top.setPosition(0, 0);
  top.setSize(sf::Vector2f(width, borderSize));
 
  left.setPosition(-borderSize, 0);
  left.setSize(sf::Vector2f(borderSize, height));
 
  right.setPosition(width, 0);
  right.setSize(sf::Vector2f(borderSize, height));
 
  bottom.setPosition(0, height-borderSize);
  bottom.setSize(sf::Vector2f(width, borderSize));
  
  b_ball = sf::CircleShape(20.f);
  b_ball.setPosition(x.getXPosition(), x.getYPosition());
    
  b_player1.setSize(sf::Vector2f(10, 50));
  b_player1.setPosition(y.getXPosition(), y.getYPosition());
  
  b_player2.setSize(sf::Vector2f(10, 50));
  b_player2.setPosition(z.getXPosition(), z.getYPosition());
 
}

int Logic::collision()
{
  sf::FloatRect t = top.getGlobalBounds();
  sf::FloatRect b = bottom.getGlobalBounds();
  sf::FloatRect l = left.getGlobalBounds();
  sf::FloatRect r = right.getGlobalBounds();
  sf::FloatRect x = b_ball.getGlobalBounds();
  sf::FloatRect y = b_player1.getGlobalBounds();
  sf::FloatRect z = b_player2.getGlobalBounds();
  
  //hits left side
  if (x.intersects(l))
    {  
      aiscore+=1;
      return ccase = 1;
    }
    //hits right side
    else if (x.intersects(r))
    {
      p1score+=1;
      return ccase = 2;
    }
    //hits top
    else if (x.intersects(t)) 
    {
      return ccase = 3;
    }
    //hits bottom
    else if (x.intersects(b))
    {
      return ccase = 4;
    }
    //hits player 1 paddle
    else if (x.intersects(y))
    {
      return ccase = 5;
    }
    //hits player 2 paddle
    else if (x.intersects(z))
    {
      return ccase = 6;
    }
    //check p1 paddle top bound
    else if (y.intersects(t))
    {
      return ccase = 7;
    }
    //check p1 paddle bottom bound
    else if (y.intersects(b))
    {
      return ccase = 8;
    }
    //check p2 paddle top bound
    else if (z.intersects(t))
    {
      return ccase = 9;
    }
    //check p2 paddle bottom bound
    else if (z.intersects(b))
    {
      return ccase = 10;
    }
  return 0;
}
  

