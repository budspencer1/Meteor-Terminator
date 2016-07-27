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


CollisionSystem::CollisionSystem( sf::Sprite *mouse, Player *player, std::list<Asteroid*> *list )
{
	pPlayerDeadSound    = new sf::Sound;
	pPlayerDeadBuffer   = new sf::SoundBuffer;
	pPlayerDeadBuffer->loadFromFile( std::string( "media/packages/content/sounds/PlayerDead.wav" ) );

	pAsteroidDestroySound  = new sf::Sound;
	pAsteroidDestroyBuffer = new sf::SoundBuffer;
	pAsteroidDestroyBuffer->loadFromFile( std::string( "media/packages/content/sounds/AsteroidDead.wav" ) );

	pPlayer			= player;
	pList			= list;
	pMouse			= mouse;

	mPlayerCanDie   = true;
}

CollisionSystem::~CollisionSystem()
{
	/* nothing, because player, list and mouse will be deleted in player class, asteroidmanager class and engine class */
}

void CollisionSystem::update( float frametime )
{
	for( auto it : *pList )
	{
		for( auto it_shot : *pPlayer->getShotList() )
		{ 
			if( Collision::PixelPerfectTest( it_shot->getSprite(), it->getSprite() ) )
			{
				it_shot->setIsAlive( false );
				pPlayer->setHits( pPlayer->getHits() + 1 );

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

					if( pPlayer->getShield() < 0 || pPlayer->getShield() == 0 )
					{
						pPlayer->setShield( 0 );
					}
				}

			else 

			if( pPlayer->getShield() == 0 || pPlayer->getShield() < 0 )
			{
				pPlayer->setLife( pPlayer->getLife() - 50*frametime );

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

	if( pPlayer->getKilledByAsteroid() == true )
	{
		std::cout << "You got fragged by Asteroid" << std::endl;
	}

	else

	{
		if( pPlayer->getIsSuicided() == true )
		{
			std::cout << "You suicided" << std::endl;
		}
	}
}