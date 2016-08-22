/* 
* File Name: Highscore.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: manage highscore routines
*/

#include "Highscore.hpp"


Highscore::Highscore()
{
	firstP			= 0;
	secondP			= 0;
	thirdP			= 0;
	fourthP			= 0;
	fifthP			= 0;
	sixthP			= 0;

	clock			= new sf::Clock;
	clock->restart();

	isShowing		= true;
}


Highscore::~Highscore()
{
	delete clock;

	clock	= nullptr;
}


int Highscore::show()
{
	std::ifstream highscore;
	highscore.open( std::string( "src/script/Highscore.hs" ) );


	if( highscore.fail() )
	{
		std::cout << "Error: Can't open Highscore.hs" << std::endl;
	}

	static unsigned int first, second , third , fourth , fifth , sixth;
	highscore >> first >> second >> third >> fourth >> fifth >> sixth;

	firstP		= first;
	secondP		= second;
	thirdP		= third;
	fourthP		= fourth;
	fifthP		= fifth;
	sixthP		= sixth;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::H ) )
	{
		if( !!isShowing )
		{
			std::cout << "Points 1st: " << first << std::endl;
			std::cout << "Points 2nd: " << second << std::endl;
			std::cout << "Points 3rd: " << third << std::endl;
			std::cout << "Points 4th: " << fourth << std::endl;
			std::cout << "Points 5th: " << fifth << std::endl;
			std::cout << "Points 6th: " << sixth << std::endl;

			isShowing = false;
		}
	}

	return 0;
}


void Highscore::update( float frametime )
{
	if( !isShowing )
	{
		if( clock->getElapsedTime().asSeconds() > 2 )
		{
			isShowing = true;
			clock->restart();
		}
	}

	this->show();
}


void Highscore::handleEvents()
{

}


void Highscore::render( sf::RenderWindow *rw )
{

}