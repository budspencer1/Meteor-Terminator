/*
* Filename: AsteroidManager.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "asteroidmanager" class 
*/


#pragma warning ( disable: 4244 )

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "AsteroidManager.hpp"
#include "Settings.inc"



AsteroidManager::AsteroidManager()
{
	pClock				= new sf::Clock();
	pClock->restart();
}

AsteroidManager::~AsteroidManager()
{
	delete pClock;
	pClock = nullptr;

	for( auto it : mAsList )
	{
		delete it;
		it = nullptr;
	}
	
	mAsList.clear();

}

void AsteroidManager::insert( Asteroid *asteroid )
{
	if( asteroid != nullptr )
	{
		mAsList.push_back( asteroid );
	}
}

void AsteroidManager::spawnAsteroid( float time )
{
	if( pClock->getElapsedTime().asSeconds() > time )
	{
		float scale			= ( ( rand() % 5 + 3 ) / 10.f );
		/* std::cout << "Scale(1): " << scale << std::endl; */

		int life            = 100;
		life = ( life * ( scale * 10 ) );

		/* std::cout << "Leben(1): " << life << std::endl; */
		
		int points = 20;
		points = ( points * ( scale * 10 ) );

		int AsteroidType = ( rand() % 2 + 1 );
		/* std::cout << "Punkte(1): " << points << std::endl; */

		int speed			= rand() % 180 + 20;
		int rotationSpeed	= rand() % 100 + 10;

		int xpos			= rand() % 1400 + 0;
		int ypos			= rand() % 300 - 300;

		if( AsteroidType == 1 )
		{
			Asteroid *a1	= new Asteroid( std::string( "media/packages/content/textures/Asteroid.png" ) , sf::Vector2f( xpos , ypos ) , sf::Vector2f( scale , scale ) ,  speed , rotationSpeed , life );
			a1->setPoints( points );
			a1->setAsteroidType( 1 );
			mAsList.push_back( a1 );
		}

		else if( AsteroidType == 2 )
		{
			Asteroid *a2	= new Asteroid( std::string( "media/packages/content/textures/Asteroid2.png" ) , sf::Vector2f( xpos , ypos ) , sf::Vector2f( scale , scale ) ,  speed , rotationSpeed , life );
			a2->setPoints( points );
			a2->setAsteroidType( 2 );
			mAsList.push_back( a2 );
		}

		pClock->restart();
	}
}

void AsteroidManager::update( float frametime )
{
	spawnAsteroid( ASTEROID_SPAWN_INTERWAL );
	checkAsteroid();

	for( auto it : mAsList )
	{
		it->update( frametime );
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F3 ) )
	{
		mAsList.clear();
	}
}

void AsteroidManager::handleEvents()
{
	for( auto it : mAsList )
	{
		it->handleEvents();
	}
}

void AsteroidManager::render( sf::RenderWindow *rw )
{
	for( auto it : mAsList )
	{
		it->render( rw );
	}
}

void AsteroidManager::checkAsteroid()
{
	for( auto it = mAsList.begin(); it != mAsList.end(); it++ )
	{
		if( ( *it )->getSprite().getPosition().y > 1000 )
		{
			delete ( *it );
			( *it ) = nullptr;

			it = mAsList.erase( it );

			/* std::cout << "Object Deleted!" << std::endl; */
		}

		if( ( *it )->getIsAlive() == false ) 
		{
			delete ( *it );
			( *it ) = nullptr;

			it = mAsList.erase( it );
		}
	}
}