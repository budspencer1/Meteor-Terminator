/*
* Filename: Security.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "security" class 
* Purpose 2: It manages all secrue trings during game
*/


#include "Security.hpp"
#include <Windows.h>



Security::Security( Asteroid *asteroid )
{
	pAsteroid = asteroid;

	setLifes( 5 );
	setUp( true );
	setDown( true );
	setLeft( true );
	setRight( true );
}

Security::~Security()
{
	/* these instances are already deleted in their own classes */
}

void Security::update( float frametime )
{
	
}

void Security::render( sf::RenderWindow *rw )
{

}

void Security::handleEvents()
{
	/* here's nothing required */
}