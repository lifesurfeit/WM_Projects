#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Viewable.h"
#include <iostream>
#include <string>
#include <sstream>

void Viewable::Draw(ball &x, player &y, player &z, int a, int b)
    {
      m_ball.setPosition(x.getXPosition(), x.getYPosition());
      m_player1.setPosition(y.getXPosition(), (int) y.getYPosition());
      m_player2.setPosition(z.getXPosition(), (int) z.getYPosition());
      m_window.clear(sf::Color::Black);
      m_line.setPosition(400, 0);
      //m_line.rotate(90);
      m_line.setFillColor(sf::Color::White);
      sf::Font font;
      // Load it from a file
      std::ostringstream os;
      os<<a;
      std::ostringstream oss;
      oss<<b;
      if (!font.loadFromFile("1900805.ttf"))
      {
        std::cout << "Error loading font\n" ;
        m_window.close();
      }
      else
      {
        m_s1.setFont(font);
      }
      m_s1.setString(os.str());
      m_s1.setCharacterSize(80);
      m_s1.setPosition(180,40);
      m_s2.setFont(font);
      m_s2.setString(oss.str());
      m_s2.setCharacterSize(80);
      m_s2.setPosition(580,40);
      m_window.draw(m_line);
      m_window.draw(m_ball);
      m_window.draw(m_player1);
      m_window.draw(m_player2);
      m_window.draw(m_s1);
      m_window.draw(m_s2);
    
    }
void Viewable::DrawTitle()
{
  sf::Font font;
  // Load it from a file
  if (!font.loadFromFile("1900805.ttf"))
  {
    std::cout << "Error loading font\n" ;
    m_window.close();
  }
  else
  {
    //find this file in the "pong" example in the SFML examples folder
    m_title.setFont(font);
    m_title.setString("PONG");
    m_title.setColor(sf::Color::White);
    m_title.setCharacterSize(100);
    m_title.setPosition(250,150);
    sf::Text text;
    text.setFont(font);
    text.setString("Press any key to start...");
    text.setCharacterSize(40);
    text.setPosition(100,500);
    m_window.clear(sf::Color::Black);
       
    m_window.draw(m_title);
    m_window.draw(text);
  }
}

void Viewable::DrawWin()
{
  sf::Font font;
  // Load it from a file
  if (!font.loadFromFile("1900805.ttf"))
  {
    std::cout << "Error loading font\n" ;
    m_window.close();
  }
  else
    m_title.setFont(font);
  m_title.setString("You Won!");
  m_title.setCharacterSize(100);
    m_title.setPosition(150,150);
  sf::Text text;
    text.setFont(font);
    text.setString("Press any key to restart.");
    text.setCharacterSize(40);
    text.setPosition(100,500);
  m_window.clear(sf::Color::Black);
  m_window.draw(m_title);
  m_window.draw(text);
}

void Viewable::DrawLoss()
{
  sf::Font font;
  // Load it from a file
  if (!font.loadFromFile("1900805.ttf"))
  {
    std::cout << "Error loading font\n" ;
    m_window.close();
  }
  else
    m_title.setFont(font);
  m_title.setString("You Lost...");
  m_title.setCharacterSize(100);
    m_title.setPosition(100,150);
  sf::Text text;
    text.setFont(font);
    text.setString("Press any key to restart.");
    text.setCharacterSize(40);
    text.setPosition(100,500);
  m_window.clear(sf::Color::Black);
  m_window.draw(m_title);
  m_window.draw(text);
}
