/*
* Filename: Weapon.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "weapon" class 
*/

#pragma warning ( disable: 4068 )
#pragma warning ( disable: 4305 )
#pragma warning ( disable: 4244 )

#include <iostream>
#include <Windows.h>
#include <list>
#include <SFML\Graphics.hpp>
#include <AccCtrl.h>

#include "Weapon.hpp"
#include "Shot.hpp"
#include "AsteroidManager.hpp"

#include "Settings.inc"


Weapon::Weapon()
{
	pFont				= new sf::Font;
	pFont->loadFromFile( std::string( "media/packages/content/fonts/Cocogoose.otf" ) );

	pTextureBullet		= new sf::Texture;
	pSpriteBullet		= new sf::Sprite;

	mAmmoLabel.setFont( *pFont );
	mAmmoLabel.setString( "Ammunition: " );
	mAmmoLabel.setPosition( sf::Vector2f( 10 , 90 ) );
	mAmmoLabel.setScale( 0.6 , 0.6 );

	mAmmoColorLabel.setFont( *pFont );
	mAmmoColorLabel.setString( AMMO + " Shots" );
	mAmmoColorLabel.setPosition( sf::Vector2f( 150 , 90 ) );
	mAmmoColorLabel.setScale( 0.6 , 0.6 );

    pOutOfAmmoSound     = new sf::Sound;
	pOutOfAmmoBuffer	= new sf::SoundBuffer;
	pOutOfAmmoBuffer->loadFromFile( std::string( "media/packages/content/sounds/OutOfAmmo.wav" ) );

	pShotPlayer			= new sf::Sound; 
	pShotSound			= new sf::SoundBuffer;
	pShotSound->loadFromFile( std::string( "media/packages/content/sounds/ShotSound1.wav" ) );

	pShotBuffer2        = new sf::SoundBuffer;
	pShotSound2			= new sf::Sound;
	pShotBuffer2->loadFromFile( std::string( "media/packages/content/sounds/ShotSound2.wav" ) );

	pWeaponSwitchBuffer	= new sf::SoundBuffer;
	pWeaponSwitchSound  = new sf::Sound;
	pWeaponSwitchBuffer->loadFromFile( std::string( "media/packages/content/sounds/SwitchWeapon.wav" ) );

	pTexture			= new sf::Texture();
	pTexture->loadFromFile( std::string( "media/packages/content/textures/Shot1.png" ) );

	pTexture2			= new sf::Texture();
	pTexture2->loadFromFile( std::string( "media/packages/content/textures/Shot2.png" ) );

	/*

	pSpriteBullet->setTexture( *pTexture );
	pSpriteBullet->setOrigin( pTexture->getSize().x/2, pTexture->getSize().y/2 );
	pSpriteBullet->setPosition( sf::Vector2f( 232 , 102.5 ) );
	pSpriteBullet->setScale( 0.1 , 0.1 );

	*/

	pWeaponCooldownSprite  = new sf::Sprite;
	pWeaponCooldownTexture = new sf::Texture;
	pWeaponCooldownTexture->loadFromFile( std::string( "media/packages/content/textures/WeaponCooldownBar.png" ) );
	
	pWeaponCooldownSprite->setTexture( *pWeaponCooldownTexture );
	pWeaponCooldownSprite->setOrigin( 0 , pWeaponCooldownTexture->getSize().y/2 );
	pWeaponCooldownSprite->setPosition( sf::Vector2f( -20 , 190 ) );
	pWeaponCooldownSprite->setScale( 0.3 , 0.15 );

	pClock1				= new sf::Clock();
	pClock1->restart();

	pClock2				= new sf::Clock();
	pClock2->restart();

	pLockClock			= new sf::Clock();
	pLockClock->restart();

	/*this->setShots( 0 );
	this->setHits( 0 );*/

	mCooldownWep1			= COOLDOWN_WEP_1;
	mCooldownWep2			= COOLDOWN_WEP_2;
	mWaittime				= WAITTIME_IN_SEC;
	mLockWep1				= true;
	mLockWep2				= true;
	mWeaponLock				= true;
	mTexOriginalSizeY		= pWeaponCooldownTexture->getSize().y;

	mPlayerPosition     = sf::Vector2f( 0 , 0 );

	mAmmo = AMMO; /* player gets 700 shots */

	this->setIsOutOfAmmo( false );
	this->setWeaponToHot( false );
	this->setWeaponTemp( 0 );
	this->setWeapon( DEFAULT_WEAPON );
	this->setWeapon1( true );
	this->setWeapon2( true );
	this->setShotsWep2( 0 );
	this->setWeapon2Temp( 1 ); /* 1 degree celsius on game start */

	mStepWP = ( pWeaponCooldownTexture->getSize().x / this->getWeapon2Temp() ) / 20;
}

Weapon::~Weapon()
{
	delete pClock1;
	delete pTexture;

	pClock1				= nullptr;
	pTexture			= nullptr;
}

void Weapon::fire()
{
	if( this->getWeapon() == 1 ) 
	{
		if( mAmmo > 0 )
		{
			/* Shot Weapon */
			if( mLockWep1 == true )
			{
				Shot* s = new Shot( mTarget, mPlayerPosition, pTexture );
				mList.push_back( s );
				mAmmo = ( mAmmo - 1 );
		
				pShotPlayer->setBuffer( *pShotSound );
				pShotPlayer->play();
		
				mLockWep1 = false;
				pClock1->restart();
			}
		}

		else if( mAmmo == 0 )
		{
			pOutOfAmmoSound->setBuffer( *pOutOfAmmoBuffer );
			pOutOfAmmoSound->play();
		}
	}
		
	else if( this->getWeapon() == 2 )
	{
		if( mLockWep2 == true )
		{
			if(  this->getWeapon2Temp() <= 18 )
			{
				Shot* s2 = new Shot( mTarget, mPlayerPosition, pTexture2 );
				mList.push_back( s2 );
				this->setShotsWep2( this->getShotsWep2() + 1 );
				this->setWeapon2Temp( this->getWeapon2Temp() + 1 * 0.2 );
				std::cout << "Minigun Temperature (C): " << ( this->getWeapon2Temp() ) << std::endl;

				if( this->getWeapon2Temp() > 13 )
				{
					std::cout << "Attention: Weapon needs cooldown in a few seconds unless you doesn't give it a break." << std::endl;
				}
	
				/* std::cout << "Shots: " << this->getShotsWep2() << std::endl; */
	
				pShotSound2->setBuffer( *pShotBuffer2 );
				pShotSound2->play();
	
				mLockWep2 = false;
				pClock2->restart();
			}
	
			else if( this->getWeapon2Temp() > 0 )
			{
				std::cout << "You can't shot. Weapon is too hot right now." << std::endl;
			}
		}
	}//mLock = false;
}

void Weapon::deleteWeapon()
{
	if( this->getWeapon() == 1 )
	{
		std::cout << "Weapon '1'(Cannon) deleted!" << std::endl;
		this->setWeapon1( false );
		this->setWeapon( 2 );
	}

	else if( this->getWeapon() == 2 )
	{
		std::cout << "Weapon '2'(Minigun) deleted!" << std::endl;
		this->setWeapon2( false );
		this->setWeapon( 1 );
	}
}

void Weapon::update( sf::Vector2f position, sf::Vector2f player, float frametime )
{ 
	if( !sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) ) 
	{
		if( this->getWeapon2Temp() > 0.1 )
		{
			this->setWeapon2Temp( this->getWeapon2Temp() - 1.5 * frametime );
		}
	}

	if( this->getWeapon2Temp() == 0 || this->getWeapon2Temp() < 0 )
	{
		this->setWeapon2Temp( 0.1 ); 
	}

	pWeaponCooldownSprite->setTextureRect( sf::IntRect( 0 , 0 , ( mStepWP * this->getWeapon2Temp() ) , pWeaponCooldownTexture->getSize().y ) );

	if( mWeaponLock == false )
	{
		if( pLockClock->getElapsedTime().asSeconds() > mWaittime )
		{
			mWeaponLock = true;
		}
	}

	if( this->getWeapon() == 1 )
	{
		if( mLockWep1 == false )
		{
			if( pClock1->getElapsedTime().asSeconds() > mCooldownWep1 )
			{
				mLockWep1 = true;
			}
		}
	}

	if( this->getWeapon() == 2 )
	{
		if( mLockWep2 == false )
		{
			if( pClock2->getElapsedTime().asSeconds() > mCooldownWep2 )
			{
				mLockWep2 = true;
			}
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad1 ) )
	{ 
		if( mWeaponLock == true )
		{
			if( this->getWeapon() == 2 || this->getWeapon() > 2 )
			{
				if( this->getWeapon1() == true )
				{
					this->setWeapon( 1 );

					std::cout << "Weapon has changed to '1'(Cannon)." << std::endl;
				}

				else

				{
					std::cout << "You deleted that weapon.(Cannon)" << std::endl;
				}
			}

			else if( this->getWeapon() == 1 )
			{
				std::cout << "Weapon has changed to '1'(Cannon)." << std::endl;

				pWeaponSwitchSound->setBuffer( *pWeaponSwitchBuffer );
				pWeaponSwitchSound->play();

				mWeaponLock = false;
				pLockClock->restart();
			}
		}

		else

		{
			/* std::cout << "You can't change Weapon right now." << std::endl; */
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad2 ) )
	{ 
		if( mWeaponLock == true )
		{
			if( this->getWeapon() == 1 || this->getWeapon() > 2 )
			{
				if( this->getWeapon2() == true )
				{
					this->setWeapon( 2 );

					std::cout << "Weapon has changed to '2'(Minigun)." << std::endl;
				}

				else

				{
					std::cout << "You deleted that weapon.(Minigun)" << std::endl;
				}
			}

			else if( this->getWeapon() == 2 )
			{
				std::cout << "Weapon has changed to '2'(Minigun)." << std::endl;

				pWeaponSwitchSound->setBuffer( *pWeaponSwitchBuffer );
				pWeaponSwitchSound->play();

				mWeaponLock = false;
				pLockClock->restart();
			}
		}

		else

		{
			/* std::cout << "You can't change Weapon right now." << std::endl; */
		}
	}

	if( this->getAmmo() > 9999 && this->getAmmo() < 100000 )
	{
		pSpriteBullet->setPosition( sf::Vector2f( 232 , 102.5 ) );
	}

	if( this->getAmmo() > 999 && this->getAmmo() < 10000 )
	{
		pSpriteBullet->setPosition( sf::Vector2f( 217 , 102.5 ) );
	}

	if( this->getAmmo() > 99 && this->getAmmo() < 1000 )
	{
		if( this->getAmmo() != 700 )
		{
			pSpriteBullet->setPosition( sf::Vector2f( 197 , 102.5 ) );
		}
	}

	if( this->getAmmo() == 700 )
	{
		pSpriteBullet->setPosition( sf::Vector2f( 205 , 102.5 ) );
	}

	if( this->getAmmo() > 9 && this->getAmmo() < 100 )
	{
		pSpriteBullet->setPosition( sf::Vector2f( 187 , 102.5 ) );
	}

	if( this->getAmmo() > 0 && this->getAmmo() < 10 )
	{
		pSpriteBullet->setPosition( sf::Vector2f( 175 , 102.5 ) );
	}

	if( this->getWeapon() == 1 )
	{
		std::stringstream as;
		as << mAmmo;

		if( mAmmo < 101 )
		{
			mAmmoColorLabel.setColor( sf::Color::Red );

			if( mAmmo == 0 )
			{
				mAmmoColorLabel.setColor( sf::Color::Red );
				mAmmoColorLabel.setString( "! Out of Ammo !" );
			}

			else 

			{
				mAmmoColorLabel.setColor( sf::Color::Red );
				mAmmoColorLabel.setString( "" + as.str() + " Shots" );
			}

		}

		else 

		{
			if( mAmmo > 100 )
			{
				mAmmoColorLabel.setColor( sf::Color::White );
				mAmmoColorLabel.setString( "" + as.str() + " Shots" );
			}
		}
	}

	if( this->getWeapon() == 2 )
	{
		mAmmoColorLabel.setColor( sf::Color::Yellow );
		mAmmoColorLabel.setString( "Unlimited" );
	}


	mPlayerPosition = player;

	//if( mLock == false )
	//	if( pClock->getElapsedTime().asSeconds() > mCooldown )
	//		mLock = true;

	/* ///////////////////////////////////////////////////////////////////////////////////////////// */
	/*
	* calculate direction 
	* of mouse pointer 
	* and player 
	*/

	mTarget = position - player;
	/* std::cout << "Target(1): " << mTarget.x << "|" << mTarget.y << std::endl; */
	const float lengh = sqrt( pow( mTarget.x , 2 ) + pow( mTarget.y , 2 ) );
    /* std::cout << "Länge: " << lengh << std::endl; */
	mTarget = ( mTarget /= lengh );
	/* std::cout << "Target(2): " << mTarget.x << "|" << mTarget.y << std::endl; */
	/* ///////////////////////////////////////////////////////////////////////////////////////////// */

	for( auto it = mList.begin(); it != mList.end(); it++ )
	{
		if( ( *it )->getIsAlive() == false )
		{
			delete ( *it );

			( *it ) = nullptr;

			it = mList.erase( it );
		}

		else 

		{
			( *it )->update( frametime ); 
		}
	}
}

void Weapon::handleEvents()
{

}

void Weapon::render( sf::RenderWindow *rw )
{
	for( auto it : mList )
	{
		rw->draw( it->getSprite() );
	}

	rw->draw( mAmmoLabel );
	rw->draw( mAmmoColorLabel );

	/*
	if( this->getAmmo() > 0 )
	{
		rw->draw( *pSpriteBullet );
	}
	*/

	if( this->getWeapon() == 2 )
	{
		rw->draw( *pWeaponCooldownSprite );
	}
}
