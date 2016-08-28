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

	firstName		= "";
	secondName		= "";
	thirdName		= "";
	fourthName		= "";
	fifthName		= "";
	sixthName		= "";

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
	std::string f , s , t , fo , fi , si;

	highscore >> first >> second >> third >> fourth >> fifth >> sixth >> f >> s >> t >> fo >> fi >> si; 

	firstP		= first;
	secondP		= second;
	thirdP		= third;
	fourthP		= fourth;
	fifthP		= fifth;
	sixthP		= sixth;

	firstName = f;
	secondName = s;
	thirdName = t;
	fourthName = fo;
	fifthName = fi;
	sixthName = si;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::H ) )
	{
		if( !!isShowing )
		{
			std::cout << "Points 1st: " << first << " " << firstName << std::endl;
			std::cout << "Points 2nd: " << second << " " << secondName << std::endl;
			std::cout << "Points 3rd: " << third << " " << thirdName << std::endl;
			std::cout << "Points 4th: " << fourth << " " << fourthName << std::endl;
			std::cout << "Points 5th: " << fifth << " " << fifthName << std::endl;
			std::cout << "Points 6th: " << sixth << " " << sixthName << "\n" << std::endl;

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