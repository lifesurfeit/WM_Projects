#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ball.h"
#include "player.h"

class Viewable
{
private:

    sf::RenderWindow& m_window;
    sf::CircleShape m_ball;
    sf::RectangleShape m_player1, m_player2;
    sf::RectangleShape m_line;
    sf::Text m_title, m_s1, m_s2;
    
public:

    Viewable(sf::RenderWindow& window) :
        m_window(window),
        m_ball(sf::CircleShape(20.f)),
	m_player1(sf::RectangleShape(sf::Vector2f(10, 50))),
	m_player2(sf::RectangleShape(sf::Vector2f(10, 50))),
	m_line(sf::RectangleShape(sf::Vector2f(3, 600)))
        
	
    {}

    void Draw(ball& x, player& y, player& z, int a, int b);
    void DrawTitle();
    void DrawWin();
    void DrawLoss();
};

