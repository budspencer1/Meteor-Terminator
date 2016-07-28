/*
* Filename: Shot.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "shot" class 
*/

#include <iostream>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <list>

#include "Shot.hpp"

Shot::Shot( sf::Vector2f direction, sf::Vector2f position, sf::Texture *texture )
{
	pClock					= new sf::Clock();

	pSprite					= new sf::Sprite;

	pSprite->setTexture( *texture );
	pSprite->setOrigin( texture->getSize().x/2, texture->getSize().y/2 );
	pSprite->setPosition( position );
	pSprite->setScale( 0.08 , 0.08 );

	mDirection = direction;

	/* variables */
	setIsAlive( true );
	mSpeed = 1300;

	pClock->restart();

	/* rotate shot to specified direction */
	pSprite->setRotation( atan2( mDirection.y , mDirection.x ) / 3.14159265359 * 180 );
	/* ///////////////////////////////////////////////////////////////////////////////////////////////// */
}

Shot::~Shot()
{
	delete pClock;
	delete pSprite;

	pClock = nullptr;
	pSprite = nullptr;
}

void Shot::handleEvents()
{

}

void Shot::update( float frametime )
{
	pSprite->move( mDirection * ( mSpeed * frametime ) );

	if( pClock->getElapsedTime().asSeconds() > 3.f )
	{
		setIsAlive( false );
	}
}

void Shot::render( sf::RenderWindow *rw )
{
	rw->draw( *pSprite );
}

