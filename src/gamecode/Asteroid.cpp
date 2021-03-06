/*
* Filename: Asteroid.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "asteroid" class 
*/


#pragma warning ( disable: 4244 )

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "Asteroid.hpp"
#include "Settings.inc"


Asteroid::Asteroid( std::string texturePath, sf::Vector2f position, sf::Vector2f scaleFactor, float speed, float rotationSpeed, float life )
{
	pClock				= new sf::Clock;
	pClock->restart();

	pSprite				= new sf::Sprite;
	pTexture			= new sf::Texture;
	pTextureTarget		= new sf::Texture;
	pTextureTarget2		= new sf::Texture;

	pTextureLifeBar     = new sf::Texture;
	pSpriteLifeBar      = new sf::Sprite;

	pTextureLifeBar->loadFromFile( std::string( "media/packages/content/textures/AsteroidLifeBar.png" ) );

	pSpriteLifeBar->setTexture( *pTextureLifeBar );
	pSpriteLifeBar->setOrigin( pTextureLifeBar->getSize().x/2, pTextureLifeBar->getSize().y/2 );
	pSpriteLifeBar->setScale( 0.5 , 0.5 );

	/* ////////////////////////////////////////// */

	pTextureTarget->loadFromFile( std::string( "media/packages/content/textures/AsteroidTarget.png" ) );
	pTextureTarget2->loadFromFile( std::string( "media/packages/content/textures/Asteroid2Target.png" ) );

	pTexture->loadFromFile( texturePath );

	sf::Image subImage;
	subImage.loadFromFile( texturePath );
	subImage.createMaskFromColor( sf::Color::White );

	pTexture->loadFromImage( subImage );
	pSprite->setTexture( *pTexture );

	pSprite->setScale( scaleFactor );
	pSprite->setPosition( position );
	pSprite->setOrigin( pTexture->getSize().x/2, pTexture->getSize().y/2 );

	mRotationSpeed		= rotationSpeed;
	mSpeed				= speed;
	asteroid			= 1;

	this->setLife( life );
	this->setIsAlive( true );
	this->setIsTarget( false );

	mStep = pTextureLifeBar->getSize().x / this->getLife();
}

Asteroid::~Asteroid()
{
	 delete pClock;
	 delete pTexture;
	 delete pSprite;
	 delete pTextureTarget;
	 delete pTextureTarget2;

	 pClock				= nullptr;
	 pTexture			= nullptr;
	 pSprite			= nullptr;
	 pTextureTarget		= nullptr;
	 pSpriteLifeBar		= nullptr;
	 pTextureLifeBar	= nullptr;
	 pTextureTarget2	= nullptr;
}

void Asteroid::update( float frametime )
{
	pSpriteLifeBar->setPosition( pSprite->getPosition().x, pSprite->getPosition().y - 25.f );
	pSprite->rotate( mRotationSpeed * frametime );
	pSprite->move( 0 , mSpeed * frametime );


	if( this->getAsteroidType() == 1 )
	{
		if( this->getIsTarget() == true )
		{
			pSprite->setTexture( *pTextureTarget );
		}

		else

		{
			pSprite->setTexture( *pTexture );
		}
	}

	else if( this->getAsteroidType() == 2 )
	{
		if( this->getIsTarget() == true )
		{
			pSprite->setTexture( *pTextureTarget2 );
		}

		else

		{
			pSprite->setTexture( *pTexture );
		}
	}

	pSpriteLifeBar->setTextureRect( sf::IntRect( 0 , 0 , ( mStep * this->getLife() ) , pTextureLifeBar->getSize().y ) );
}

void Asteroid::render( sf::RenderWindow *rw )
{
	rw->draw( *pSprite );

	if( this->getIsTarget() == true )
	{
		rw->draw( *pSpriteLifeBar );
	}
}

void Asteroid::handleEvents()
{

}

void Asteroid::loadAsteroid()
{

}

