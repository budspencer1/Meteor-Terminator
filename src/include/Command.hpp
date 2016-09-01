/*
* File Name: Command.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: declare all commands for ingame console
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <sstream>

#include "Player.hpp"
#include "Weapon.hpp"
#include "Security.hpp"


class Command 
{


public: 

    Command()
	{
	}

	~Command()
	{
	}

	void handleEvents();


    static void help( sf::Text *label , std::string *text )
	{
		*text = "[Command Help]\n/help /screenshot /stats /pause /resume /quit\n/menu /restart /suicide /respawn";
		label->setString( static_cast<std::string>( *text ) );
	}

    unsigned int num;
	const unsigned int getNum() { return num; };

	int numb() 
	{
		return ( std::rand() % 1000000000000000 );
	}

	void screenshot( sf::RenderWindow *rw , sf::Text *label , std::string *text )
	{
		std::stringstream number;
		number << numb();

		sf::Image screenshot = rw->capture();

		*text = std::string( "[Screenshot]\nScreenshot has been saved under\n'screenshots/screenshot_" + number.str() + ".bmp" );
		label->setString( std::string( *text ) );

		screenshot.saveToFile( std::string( "screenshots/screenshot_" + number.str() + ".bmp" ) );
	}


	static void stats( Player *player , sf::Text *label , std::string *text )
	{
		static unsigned int frags , shots , points;

		frags = player->getFrags();
		shots = player->getShots();
		points = player->getPoints();

		float posx = player->getSprite().getPosition().x;
		float posy = player->getSprite().getPosition().y;

		std::stringstream f , s , p , x , y , n;
		f << frags;
		s << shots;
		p << points;
		x << posx;
		y << posy;

		*text = "[Stats]\nFrags: " + f.str() + "\nShots: " + s.str() + "\nPoints: " + p.str() + "\nPosition(X , Y): " + x.str() + " , " + y.str() + "\n";
		label->setString( std::string( *text ) );
	}

	static void restart( Player *player )
	{
		player->restart();
	}

	static void suicide( Player *player )
	{
		player->suicide();
	}

	static void respawn( Player *player )
	{
		player->respawn();
	}


private:


};

#endif