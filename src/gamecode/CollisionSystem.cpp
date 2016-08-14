/*
* Filename: CollisionSystem.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "collisionsystem" class 
*/


#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "Collision.hpp"
#include "CollisionSystem.hpp"

#include "Settings.inc"


CollisionSystem::CollisionSystem( sf::Sprite *mouse, Player *player, std::list<Asteroid*> *list )
{
	pHitClock			= new sf::Clock;
	pHitClock->restart();

	pPlayerDeadSound    = new sf::Sound; 
	pPlayerDeadBuffer   = new sf::SoundBuffer;
	pPlayerDeadBuffer->loadFromFile( std::string( "media/packages/content/sounds/PlayerDead.wav" ) );

	pAsteroidDestroySound  = new sf::Sound;
	pAsteroidDestroyBuffer = new sf::SoundBuffer;
	pAsteroidDestroyBuffer->loadFromFile( std::string( "media/packages/content/sounds/AsteroidDead.wav" ) );

	pAsteroidItemPickBuffer			= new sf::SoundBuffer;
	pAsteroidItemPickSound			= new sf::Sound;
	pAsteroidItemPickBuffer->loadFromFile( std::string( "media/packages/content/sounds/PickAsteroidItem.wav" ) );

	pTexture1			   = new sf::Texture();
	pTexture1->loadFromFile( std::string( "media/packages/content/textures/HealthCrossRed.png" ) );

	pTexture2			   = new sf::Texture();
	pTexture2->loadFromFile( std::string( "media/packages/content/textures/Shield.png" ) );

	pTexture3				= new sf::Texture();
	pTexture3->loadFromFile( std::string( "media/packages/content/textures/HealthCrossGreen.png" ) );

	pPlayer			= player;
	pList			= list;
	pMouse			= mouse;

	mPlayerCanDie   = true;
	mRemainingLife	= 0;

	this->setIsHit( false );
}

CollisionSystem::~CollisionSystem()
{
	delete pTexture1;
	delete pTexture2;
	delete pTexture3;

	delete pPlayerDeadBuffer;
	delete pPlayerDeadSound;
	delete pAsteroidDestroyBuffer;
	delete pAsteroidDestroySound;
	delete pAsteroidItemPickBuffer;
	delete pAsteroidItemPickSound;

	pTexture1					= nullptr;
	pTexture2					= nullptr;
	pTexture3					= nullptr;

	pPlayerDeadBuffer			= nullptr;
	pPlayerDeadSound			= nullptr;
	pAsteroidDestroyBuffer		= nullptr;
	pAsteroidDestroySound		= nullptr;
	pAsteroidItemPickBuffer		= nullptr;
	pAsteroidItemPickSound		= nullptr;

}

bool CollisionSystem::AsteroidHasItem()
{
	mRandomValue = ( rand() % 9 + 1 );

	if( mRandomValue == 4 )
	{
		return true;
	}

	else

	{
		return false;
	}
}

void CollisionSystem::update( float frametime )
{
	if( this->getIsHit() == true )
	{
		if( pHitClock->getElapsedTime().asSeconds() > HIT_TIME )
		{
			this->setIsHit( false );
		}
	}

	for( auto it : *pList )
	{
		for( auto it_shot : *pPlayer->getShotList() )
		{ 
			if( Collision::PixelPerfectTest( it_shot->getSprite(), it->getSprite() ) )
			{
				it_shot->setIsAlive( false );
				pPlayer->setHits( pPlayer->getHits() + 1 );
				this->setIsHit( true );

				if( pPlayer->getPlayerWeapon() == 1 )
				{
					it->setLife( it->getLife() - 50 );
				}

				else if( pPlayer->getPlayerWeapon() == 2 )
				{
					it->setLife( it->getLife() - 10 );
				}

				if( it->getLife() == 0 || it->getLife() < 0 )
				{
					if( AsteroidHasItem() == true )
					{
						if( pPlayer->getShield() < SHIELD && pPlayer->getLife() == LIFE )
						{
							Health *h = new Health( pTexture2 , sf::Vector2f( it->getSprite().getPosition().x , it->getSprite().getPosition().y ) , ( 100 * frametime ) , h->getValue() );
							mHealthList.push_back( h );
						}

						else if( pPlayer->getShield() == 0 && pPlayer->getLife() < LIFE )
						{
							Health *h = new Health( pTexture1 , sf::Vector2f( it->getSprite().getPosition().x , it->getSprite().getPosition().y ) , ( 100 * frametime ) , h->getValue() );
							mHealthList.push_back( h );
						}

						else if( pPlayer->getShield() == SHIELD && pPlayer->getLife() == LIFE )
						{
							Health *h = new Health( pTexture3 , sf::Vector2f( it->getSprite().getPosition().x , it->getSprite().getPosition().y ) , ( 100 * frametime ) , h->getValue() );
							mHealthList.push_back( h );
						}

						std::cout << "Health spawned." << std::endl;
					}

					it->setIsAlive( false );

					std::cout << "You fragged Asteroid" << std::endl;

					pPlayer->setFrags( pPlayer->getFrags() + 1 );

					pAsteroidDestroySound->setBuffer( *pAsteroidDestroyBuffer );
					pAsteroidDestroySound->play();
				}	

				if ( it->getIsAlive() == false )
				{
					if( pPlayer->getIsAlive() == true )
					{
						if( pPlayer->getGameOver() == false )
						{
							/* Player Score System */
							pPlayer->setPoints( pPlayer->getPoints() + it->getPoints() );
							pPlayer->setTotalPoints( pPlayer->getTotalPoints() + it->getPoints() );
						}
					}
				}

				pHitClock->restart();
			}

			if( Collision::PixelPerfectTest( pPlayer->getSprite(), it->getSprite() ) && Collision::PixelPerfectTest( it_shot->getSprite(), it->getSprite() ) )
			{
				if( it->getIsAlive() == false )
				{
					pPlayer->setFrags( pPlayer->getFrags() - 1 );
					std::cout << "Fragging with Weapon and Body isn't allowd in space ;)" << std::endl;
				}
			}
		}

		if( Collision::PixelPerfectTest( pPlayer->getSprite(), it->getSprite() ) )
		{
			if( pPlayer->getGameOver() == false )
			{
				if( pPlayer->getIsAlive() == true )
				{
					it->setLife( it->getLife() - 100*frametime );
				}

				if ( pPlayer->getShield() > 0 )
				{
					pPlayer->setShield( pPlayer->getShield() - 50*frametime );
					/* std::cout << "Shield: " << pPlayer->getShield() << std::endl; */

					if( pPlayer->getShield() < 0 || pPlayer->getShield() == 0 )
					{
						pPlayer->setShield( 0 );
					}
				}

			else 

			if( pPlayer->getShield() == 0 || pPlayer->getShield() < 0 )
			{
				pPlayer->setLife( pPlayer->getLife() - 50*frametime );
				/* std::cout << "Life: " << pPlayer->getLife() << std::endl; */

				if( pPlayer->getLife() < 0 )
				{
					pPlayer->setLife( 0 );
				}

				if( pPlayer->getLife() == 0 )
				{
					if( mPlayerCanDie == true )
					{
						pPlayerDeadSound->setBuffer( *pPlayerDeadBuffer );
						pPlayerDeadSound->play();

						pPlayer->setDeaths( pPlayer->getDeaths() + 1 );

						pPlayer->setKilledByAsteroid( true );
					}

					mPlayerCanDie = false;
				}

				else 

				{
					mPlayerCanDie = true;
				}
			}

			
			if( it->getLife() == 0 || it->getLife() < 0 )
			{
				it->setIsAlive( false );
				pPlayer->setFrags( pPlayer->getFrags() + 1 );

				std::cout << "You fragged Asteroid" << std::endl;

				pAsteroidDestroySound->setBuffer( *pAsteroidDestroyBuffer );
				pAsteroidDestroySound->play();

			}

			if ( it->getIsAlive() == false )
			{
				/* Player Score System */
				if( pPlayer->getIsAlive() == true )
				{
					pPlayer->setPoints( pPlayer->getPoints() + it->getPoints() );
					pPlayer->setTotalPoints( pPlayer->getTotalPoints() + it->getPoints() );
					}
				}
			}
		}

		/*
		* collision between mouse curser and asteroid
		*/

		if( Collision::PixelPerfectTest( *pMouse, it->getSprite() ) )
		{
			it->setIsTarget( true );
		}

		else 

		{
			it->setIsTarget( false );
		}

		
	    if( it->getLife() == 0 || it->getLife() < 0 )
		{
			it->setIsAlive( false );
		}
	}

	for( auto it = mHealthList.begin(); it != mHealthList.end(); it++ )
	{
		if( ( *it )->getIsAlive() == false )
		{
			delete ( *it );

			( *it ) = nullptr;

			it = mHealthList.erase( it );
		}

		else 

		{
			( *it )->update( frametime ); 
		}
	}

	for( auto it : mHealthList ) 
	{
		if( Collision::PixelPerfectTest( pPlayer->getSprite() , it->getSprite() ) )
		{
			if( pPlayer->getLife() < LIFE || pPlayer->getShield() < SHIELD )
			{
				if( pPlayer->getShield() < SHIELD && pPlayer->getLife() == LIFE )
				{
					pPlayer->setShield( pPlayer->getShield() + it->getValue() );

					if( pPlayer->getShield() > SHIELD )
					{
						pPlayer->setShield( SHIELD );
					}

					pAsteroidItemPickSound->setBuffer( *pAsteroidItemPickBuffer ); /* play sound */
					pAsteroidItemPickSound->play();

					it->setIsAlive( false );
				}

				else if( pPlayer->getShield() == 0 && pPlayer->getLife() < LIFE )
				{
					pPlayer->setLife( pPlayer->getLife() + it->getValue() );

					pAsteroidItemPickSound->setBuffer( *pAsteroidItemPickBuffer ); /* play sound */
					pAsteroidItemPickSound->play();

					it->setIsAlive( false );

					if( pPlayer->getLife() > LIFE )
					{
						pPlayer->setLife( LIFE );
					}
				}

				else if( pPlayer->getLife() == LIFE && pPlayer->getShield() == SHIELD )
				{
					/* std::cout << "You got full life and armour." << std::endl; */
				}
			}
		}
	}
}

void CollisionSystem::handleEvents()
{

}

void CollisionSystem::render( sf::RenderWindow *rw )
{
	for( auto it : mHealthList )
	{
		rw->draw( it->getSprite() );
	}
}