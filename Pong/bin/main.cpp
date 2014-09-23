#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Viewable.h"
#include "Logic.h"
//#include "Sounds.h"
#include <iostream>
#include <time.h>

int clamp (const int x, const int a, const int b)
{
    return std::min(std::max(a,x),b);
}

int main(int argc, char** argv)
{
 
    const int width = 800;
    const int height= 600;
    const int borderSize= 12;
    const int margin = 50;
    const int moveDistance = 5;
    
    //Sounds sound;
    sf::SoundBuffer buff, buff1, buff2, buff3;
    sf::Sound intro, blip, win, lose;
    
    if(!buff.loadFromFile("intro.wav"))
    {
      std::cout<<"Sound failed to load"<<std::endl;
    }else
    {
     
      intro.setBuffer(buff);
    }
    
    if(!buff1.loadFromFile("blip.wav"))
    {
      std::cout<<"Sound failed to load"<<std::endl;
    }else
    {
     
      blip.setBuffer(buff1);
    }
    
    if(!buff2.loadFromFile("yay.wav"))
    {
      std::cout<<"Sound failed to load"<<std::endl;
    }else
    {
     
      win.setBuffer(buff2);
    }
    
    if(!buff3.loadFromFile("bad.flac"))
    {
      std::cout<<"Sound failed to load"<<std::endl;
    }else
    {
     
      lose.setBuffer(buff3);
    }
    
    
    sf::RenderWindow window(sf::VideoMode(width, height), "PONG");

    Viewable myObject(window);

    ball myBall(380, 280);
    player myPlayer(100, 275.0);
    player AI(700, 275.0);
    
    enum states {TITLE, PLAY, WON, LOST};
    int gameState=TITLE;
    
    sf::Vector2<float> ballSpeed(0.7,0.7);
    int myScore = 0, AIScore = 0;
    int u;
    float prevx = myBall.getXPosition();
    float prevy = myBall.getYPosition();
    
    srand (time(NULL));
    
    while(window.isOpen())
    {
      sf::Clock clock;
      float r = rand()%100/100;
      switch(gameState)
      {
	case TITLE:
	  intro.play();
	  myObject.DrawTitle();
	  break;
	case PLAY:
	  myObject.Draw(myBall, myPlayer, AI, myScore, AIScore);
	  break;
	case WON:
	  myObject.DrawWin();
	  break;
	case LOST:
	  myObject.DrawLoss();
	  break;
      }
       
        window.display();
       
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed)
                window.close();
	    else if ((ev.type == sf::Event::KeyPressed) && (gameState != PLAY))
                gameState=PLAY;
	}
       if(gameState !=PLAY)
	 continue;
              
       sf::Time time1 = clock.getElapsedTime();
       float timedelta = time1.asMilliseconds();
       //std::cout<<timedelta<<std::endl;
       
       //automove p2
       if(myBall.getYPosition()<AI.getYPosition())
	 AI.move(-moveDistance/10.0*timedelta);
       else if(myBall.getYPosition()>AI.getYPosition())
	 AI.move(moveDistance/10.0*timedelta);
       
       //move p1
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	  myPlayer.move(-moveDistance/8.0*timedelta);
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	 myPlayer.move(moveDistance/8.0*timedelta);
       
       sf::Time time2 = clock.restart();
       
       Logic gamelog = Logic(myBall, myPlayer, AI);
       
       switch(gamelog.collision())
       {
	//check paddle bounds
	case 7:
	  myPlayer.setYPosition(clamp(myPlayer.getYPosition(),borderSize,height-borderSize-50-5));
	  break;
	case 8:
	  myPlayer.setYPosition(clamp(myPlayer.getYPosition(),borderSize,height-borderSize-50-5));
	  break;
	case 9:
	  AI.setYPosition(clamp(AI.getYPosition(),borderSize,height-borderSize-50-5));
	  break;
	case 10:
	  AI.setYPosition(clamp(AI.getYPosition(),borderSize,height-borderSize-50-5));
	  break;
	
	//check wall bounce
	case 3:  //top
	 ballSpeed.y = -ballSpeed.y;
	 if(myBall.getXPosition()<prevx)
	   myBall.move((prevx-myBall.getXPosition())*r*timedelta,(prevy-myBall.getYPosition())*r*timedelta);
	 else
	   myBall.move((myBall.getXPosition()-prevx)*r*timedelta,(prevy-myBall.getYPosition())*r*timedelta);
	 blip.play(); 
	 break;
	 
	case 4:  //bottom 
	 ballSpeed.y = -ballSpeed.y;
	 if(myBall.getXPosition()<prevx)
	   myBall.move((prevx-myBall.getXPosition())*r*timedelta,(prevy-myBall.getYPosition())*r*timedelta);
	 else
	   myBall.move((myBall.getXPosition()-prevx)*r*timedelta,(prevy-myBall.getYPosition())*r*timedelta);
	 blip.play();
	 break;
	
	case 5:  //hits p1 paddle
	 ballSpeed.x = -ballSpeed.x;
	 myBall.move((prevx-myBall.getXPosition())*r*timedelta,(myBall.getYPosition()-prevy)*r*timedelta);
	 ballSpeed.x = ballSpeed.x+.02;
	 ballSpeed.y = ballSpeed.y+.02;
	 blip.play();
	 break;
	 
	case 6: //hits p2 paddle 
	 ballSpeed.x = -ballSpeed.x;
	 myBall.move((myBall.getXPosition()-prevx)*r*timedelta,(myBall.getYPosition()-prevy)*r*timedelta);
	 ballSpeed.x = ballSpeed.x+.02;
	 ballSpeed.y = ballSpeed.y+.02;
	 blip.play();
	 break;
	//check scoring
	case 1:  //left 
	 if (AIScore<gamelog.aiscore)
	 {
	   AIScore+=1;
	   std::cout<<"Player 2 scored. Score is now " << myScore << " to " << AIScore << std::endl;
	   myBall.setPosition(380,280);
	   ballSpeed.x = -0.7;
	   ballSpeed.y = 0.7;
	 }
	 else
	 {
	   std::cout<<"Error updating score."<<std::endl;
	   exit (EXIT_FAILURE);
	 }
	 blip.play();
	 break;
	case 2:  //right 
	 blip.play();
	 if (myScore<gamelog.p1score)
	 {
	   myScore+=1;
	   std::cout<<"You scored! Score is now " << myScore << " to " << AIScore << std::endl;
	   myBall.setPosition(380,280);
	   ballSpeed.x = 0.7;
	   ballSpeed.y = 0.7;
	 }
	 else
	 {
	   std::cout<<"Error updating score."<<std::endl;
	   exit (EXIT_FAILURE);
	 }
	 
	 break;
        }
         prevx = myBall.getXPosition();
	 prevy = myBall.getYPosition();
        
	if (myScore >10)
	{ 
	  std::cout<<"You won!"<<std::endl;
	  gameState=WON;
	  myScore=0;
	  AIScore=0;
	  win.play();
	}
	else if (AIScore >10)
	{
          std::cout<<"You lost!"<<std::endl;  
	  gameState=LOST;
	  myScore=0;
	  AIScore=0;
	  lose.play();
	}
	myBall.move(ballSpeed.x,ballSpeed.y);
    }

    return 0;
}