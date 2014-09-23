#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ball.h"
#include "player.h"

class Logic
{
protected:
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::CircleShape b_ball;
    sf::RectangleShape b_player1, b_player2;
public:
  int ccase, p1score, aiscore;
  Logic(ball &x, player &y, player &z);

  int collision();
};