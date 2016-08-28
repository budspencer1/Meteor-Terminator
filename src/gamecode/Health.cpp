/* 
* File Name: Health.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: Manage giving player health on asteroid kill, if asteroid got health item 
*/


#pragma warning ( disable: 4244 )
#pragma warning ( disable: 4305 )

#include "Health.hpp"
#include "Settings.inc"



Health::Health( sf::Texture *texture , sf::Vector2f position , float speed , float value )
{
	pClock			= new sf::Clock();
	pClock->restart();

	pSprite			= new sf::Sprite();
	pSprite->setTexture( *texture );
	pSprite->setOrigin( texture->getSize().x/2, texture->getSize().y/2 );
	pSprite->setPosition( position );
	pSprite->setScale( 0.13 , 0.13 );


	mSpeed = 70;

	this->setIsAlive( true );
	this->setValue( LIFE / 7 );
}


Health::~Health()
{
	delete pClock;
	delete pSprite;

	pClock		= nullptr;
	pSprite		= nullptr;
}


void Health::update( float frametime )
{
	pSprite->move( 0 , ( mSpeed * frametime ) );

	if( pSprite->getPosition().y > ( RES_Y + 200 ) || pClock->getElapsedTime().asSeconds() > 5 )
	{
		this->setIsAlive( false );
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad9 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num0 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F3 ) )
	{
		mHealthList.clear();
	}
}


void Health::handleEvents()
{

}

void Health::render( sf::RenderWindow *rw )
{
	if( this->getIsAlive() == true )
	{
		rw->draw( *pSprite );
	}
}