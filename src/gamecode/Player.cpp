/*
* Filename: Player.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "player" class 
* Note: More complex than engine class :3
*/


#pragma warning ( disable: 4305 ) /* disable some warnings */
#pragma warning ( disable: 4804 ) /* disable some warnings */
#pragma warning ( disable: 4244 ) /* disable some warnings */

#if ( !defined TERMINATOR ) 
	#define TERMINATOR 
#endif

#include <iostream> 
#include <Windows.h>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>

#include "Player.hpp"
#include "Weapon.hpp"

#include "Settings.inc"


Player::Player( std::string texturePath, sf::Vector2f position )
{
	pTimeSeconds			= new sf::Clock();
	pTimeSeconds->restart();

	pTimeMinutes			= new sf::Clock;
	pTimeMinutes->restart();

	pCommandClock			= new sf::Clock();
	pCommandClock->restart();

	pClock					= new sf::Clock();
	pClock->restart();

	pWeaponSwitchClock		= new sf::Clock();
	pWeaponSwitchClock->restart();

	pTextureH1			= new sf::Texture;
	pSpriteH1			= new sf::Sprite;
	pTextureH2			= new sf::Texture;
	pSpriteH2			= new sf::Sprite;
	pTextureH3			= new sf::Texture;
	pSpriteH3			= new sf::Sprite;

	pTextureH1->loadFromFile( std::string( "media/packages/content/textures/Health.png" ) );
	pSpriteH1->setTexture( *pTextureH1 );
	pSpriteH1->setOrigin( pTextureH1->getSize().x/2, pTextureH1->getSize().y/2 );
	pSpriteH1->setPosition( sf::Vector2f( 1200 , 34 ) );
	pSpriteH1->setScale( 0.25 , 0.25 );

	pTextureH2->loadFromFile( std::string( "media/packages/content/textures/Health.png" ) );
	pSpriteH2->setTexture( *pTextureH2 );
	pSpriteH2->setOrigin( pTextureH2->getSize().x/2, pTextureH2->getSize().y/2 );
	pSpriteH2->setPosition( sf::Vector2f( 1280 , 34 ) );
	pSpriteH2->setScale( 0.25 , 0.25 );

	pTextureH3->loadFromFile( std::string( "media/packages/content/textures/Health.png" ) );
	pSpriteH3->setTexture( *pTextureH3 );
	pSpriteH3->setOrigin( pTextureH3->getSize().x/2, pTextureH3->getSize().y/2 );
	pSpriteH3->setPosition( sf::Vector2f( 1360 , 34 ) );
	pSpriteH3->setScale( 0.25 , 0.25 );


	pGameRestartSound       = new sf::Sound;
	pGameRestartBuffer      = new sf::SoundBuffer;
	pGameRestartBuffer->loadFromFile( std::string( "media/packages/content/sounds/RestartGame.wav" ) );

	pPlayerRespawnSound		= new sf::Sound;
	pPlayerRespawnBuffer	= new sf::SoundBuffer;
	pPlayerRespawnBuffer->loadFromFile( std::string( "media/packages/content/sounds/PlayerRespawn.wav" ) );

	pPlayerDeadSound    = new sf::Sound;
	pPlayerDeadBuffer   = new sf::SoundBuffer;
	pPlayerDeadBuffer->loadFromFile( std::string( "media/packages/content/sounds/PlayerDead.wav" ) );

	/*
	pWeaponSwitchSound  = new sf::Sound;
	pWeaponSwitchBuffer = new sf::SoundBuffer;
	pWeaponSwitchBuffer->loadFromFile( std::string( "media/packages/content/sounds/SwitchWeapon.wav" ) );
	*/

	pFont				= new sf::Font;
	pFont->loadFromFile( std::string( "media/packages/content/fonts/Cocogoose.otf" ) );

	mStatusLabel.setFont( *pFont );
	mStatusLabel.setString( "" );
	mStatusLabel.setPosition( sf::Vector2f( 10 , 825 ) );
	mStatusLabel.setScale( 0.6 , 0.6 );

	mFragsLabel.setFont( *pFont );
	mFragsLabel.setString( "Frags: " );
	mFragsLabel.setPosition( sf::Vector2f( 10 , 130 ) );
	mFragsLabel.setScale( 0.6 , 0.6 );

	mGameOverLabel.setFont( *pFont );
	mGameOverLabel.setColor( sf::Color( 48 , 223 , 217 ) );
	mGameOverLabel.setString( "! Game Over !" );
	mGameOverLabel.setOrigin( mGameOverLabel.getScale().x / 2 , mGameOverLabel.getScale().y / 2 );
	mGameOverLabel.setPosition( sf::Vector2f( 320 , 400 ) );
	mGameOverLabel.setCharacterSize( 100 );

	mLifesLabel.setFont( *pFont );
	mLifesLabel.setString( "Lifes: " );
	mLifesLabel.setPosition( sf::Vector2f( 1100 , 10 ) );
	mLifesLabel.setScale( 0.6 , 0.6 );

	mPosXLabel.setFont( *pFont );
	mPosXLabel.setString( "Position [X]: " );
	mPosXLabel.setPosition( sf::Vector2f( 1250 , 850 ) );
	mPosXLabel.setScale( 0.4 , 0.4 );

	mPosYLabel.setFont( *pFont );
	mPosYLabel.setString( "Position [Y]: " );
	mPosYLabel.setPosition( sf::Vector2f( 1250 , 870 ) );
	mPosYLabel.setScale( 0.4 , 0.4 );
	
	mTimeRemainingLabel.setFont( *pFont );
	mTimeRemainingLabel.setString( "Game Time (in Seconds): " );
	mTimeRemainingLabel.setPosition( sf::Vector2f( 10 , 865 ) );
	mTimeRemainingLabel.setScale( 0.6 , 0.6 );

	mGameScoreLabel.setFont( *pFont );
	mGameScoreLabel.setString( "Gamescore: " );
	mGameScoreLabel.setPosition( sf::Vector2f( 10 , 10 ) );
	mGameScoreLabel.setScale( 0.6 , 0.6 );

	mLevelLabel.setFont( *pFont );
	mLevelLabel.setString( "Level: " );
	mLevelLabel.setPosition( sf::Vector2f( 10 , 50 ) );
	mLevelLabel.setScale( 0.6 , 0.6 );


	pSprite				= new sf::Sprite;
	pTexture			= new sf::Texture;

	pTextureShield	    = new sf::Texture;
	pSpriteShield       = new sf::Sprite;

	pSpriteLifebar		= new sf::Sprite;
	pTextureLifebar		= new sf::Texture;

	pTextureShieldbar   = new sf::Texture;
	pSpriteShieldbar    = new sf::Sprite;


	/* ////////////////////////////////////////// */

	pTextureLifebar->loadFromFile( std::string( "media/packages/content/textures/LifeBar.png" ) );

	pSpriteLifebar->setTexture( *pTextureLifebar );
	pSpriteLifebar->setOrigin( pTextureLifebar->getSize().x/2, pTextureLifebar->getSize().y/2 );
	pSpriteLifebar->setScale( 0.55 , 0.55 );

	/* ////////////////////////////////////////// */

	pTextureShieldbar->loadFromFile( std::string( "media/packages/content/textures/ShieldLifeBar.png" ) );

	pSpriteShieldbar->setTexture( *pTextureShieldbar );
	pSpriteShieldbar->setOrigin( pTextureShieldbar->getSize().x/2, pTextureShieldbar->getSize().y/2 );
	pSpriteShieldbar->setScale( 0.55 , 0.55 );

	/* ////////////////////////////////////////// */

	pTexture->loadFromFile( texturePath );

	sf::Image subImage;
	subImage.loadFromFile( texturePath );
	subImage.createMaskFromColor( sf::Color::White );

	pTexture->loadFromImage( subImage );
	pSprite->setTexture( *pTexture );

    pTextureShield->loadFromFile( std::string( "media/packages/content/textures/PlayerShield.png" ) );
	pSpriteShield->setTexture( *pTextureShield );
	pSpriteShield->setScale( 0.20 , 0.20 );
	pSpriteShield->setOrigin( pTextureShield->getSize().x/2, pTextureShield->getSize().y/2 );

	pSprite->setScale( 0.20 , 0.20 );
	pSprite->setOrigin( pTexture->getSize().x/2, pTexture->getSize().y/2 );
	pSprite->setPosition( position );

	pSpriteShield->setPosition( pSprite->getPosition() );

	this->setShield( SHIELD );
	this->setPoints( 0 );
	this->setLife( LIFE );
	this->setIsAlive( true );
	this->setLevel( 1 );
	this->setHasAmmo( true );
	this->setFrags( 0 );
	this->setDeaths( 0 );
	this->setGameOver( false );
	this->setTotalPoints( 0 );
	this->setShots( 1 );
	this->setHits( 1 );
	this->setLifes( LIFES );
	this->setKilledByAsteroid( false );
	this->setSeconds( 0 );
	this->setPlayerWeapon( 1 );

	mStep = 255 / getShield(); /* 255 = maximum alpha value */

	mCanMoveUp				= true;
	mCanMoveDown			= true;
	mCanMoveLeft			= true;
	mCanMoveRight			= true;

	pWeapon					= new Weapon();
	//pCommandHandler			= new CommandHandler();

	mMousePosition			= sf::Vector2f( 0 , 0 );

	mStepHP = pTextureLifebar->getSize().x / this->getLife();
	mStepSH = pTextureShieldbar->getSize().x / this->getShield();

	mGameTime = 300; /* 5 minutes for every level */

	mCooldown			= COOLDOWN_WEP_1;
	mLock				= true;
	mCommandLock		= true;
	mCommandWaittime    = COMMAND_OVERFLOW_TIME;
	mCountdownTime		= 5;
	mLockSeconds		= 2;
	mWeaponSwitchLock	= true;
	minutes				= 0;
}

Player::~Player()
{
	 delete pTexture;
	 delete pSprite;

	 delete pTextureShield;
	 delete pSpriteShield;

	 delete pTextureLifebar;
	 delete pSpriteLifebar;

	 delete pSpriteShieldbar;
	 delete pTextureShieldbar;

	 delete pFont;

	 delete pPlayerDeadSound;
	 delete pPlayerDeadBuffer;

	 delete pPlayerRespawnSound;
	 delete pPlayerRespawnBuffer;

	 delete pGameRestartBuffer;
	 delete pGameRestartSound;

	 delete pClock;
	 delete pTimeSeconds;
	 delete pTimeMinutes;

	 /*
	 delete pWeaponSwitchBuffer;
	 delete pWeaponSwitchSound;
	 */

	 delete pWeaponSwitchClock;


	 pTexture				= nullptr;
	 pSprite				= nullptr;

	 pTextureShield			= nullptr;
	 pSpriteShield			= nullptr;

	 pTextureLifebar		= nullptr;
	 pSpriteLifebar			= nullptr;

	 pSpriteShieldbar		= nullptr;
	 pTextureShieldbar		= nullptr;

	 pFont					= nullptr;

	 pPlayerDeadSound		= nullptr;
	 pPlayerDeadBuffer	    = nullptr;

	 pPlayerRespawnBuffer   = nullptr;
	 pPlayerRespawnSound    = nullptr;

	 pGameRestartBuffer		= nullptr;
	 pGameRestartSound		= nullptr;

	 pClock					= nullptr;	
	 pTimeSeconds			= nullptr;
	 pTimeMinutes			= nullptr;
	 pWeaponSwitchClock     = nullptr;
	 /*
	 pWeaponSwitchBuffer	= nullptr;
	 pWeaponSwitchSound		= nullptr;
	 */
}

void Player::suicide()
{
	if( this->getIsAlive() == true && this->getGameOver() == false )
	{
		this->setShield( 0 );
		this->setLife( 0 );
		this->setDeaths( this->getDeaths() + 1 );
		this->setLifes( this->getLifes() - 1 );
		this->setKilledByAsteroid( false );
		this->setIsSuicided( true );

		mFragsLabel.setPosition( sf::Vector2f( 10 , 90 ) );

		pPlayerDeadSound->setVolume( 100 );
		pPlayerDeadSound->setBuffer( *pPlayerDeadBuffer );
		pPlayerDeadSound->play();

		std::cout << "You suicided" << std::endl;

		mStatusLabel.setColor( sf::Color::Red );
		mStatusLabel.setString( "Suicided" );
	}
}

void Player::respawn()
{
	if( this->getIsAlive() == false && this->getGameOver() == false )
	{
		this->setIsAlive( true );
		this->setShield( SHIELD );
		this->setLife( LIFE );
		this->setIsAlive( true );
		this->setHasAmmo( true );
		this->setShots( 0 );
		this->setHits( 0 );
		this->setKilledByAsteroid( false );
		this->setIsSuicided( false );
		this->setPlayerWeapon( 1 );

		pSprite->setPosition( sf::Vector2f( PLAYER_X_POS , PLAYER_Y_POS ) );

		pWeapon->setAmmo( AMMO / 2 );
		pWeapon->setIsOutOfAmmo( false );
		pWeapon->setShotsWep2( 0 );
		pWeapon->setWeapon( 1 );
		pWeapon->setWeapon2Temp( 0.1 );
		pWeapon->setWeaponToHot( false );

		mFragsLabel.setPosition( sf::Vector2f( 10 , 130 ) );

		pPlayerRespawnSound->setBuffer( *pPlayerRespawnBuffer );
		pPlayerRespawnSound->play();

		mCanMoveUp				= true;
		mCanMoveDown			= true;
		mCanMoveLeft			= true;
		mCanMoveRight			= true;

		std::cout << "You respawned. Remaining Lifes: " << this->getLifes() << std::endl;
	}
}

void Player::restart()
{
	if( mCommandLock == true )
	{
		this->setShield( SHIELD );
		this->setPoints( 0 );
		this->setLife( LIFE );
		this->setIsAlive( true );
		this->setLevel( 1 );
		this->setHasAmmo( true );
		this->setFrags( 0 );
		this->setDeaths( 0 );
		this->setGameOver( false );
		this->setTotalPoints( 0 );
		this->setShots( 0 );
		this->setHits( 0 );
		this->setLifes( LIFES );
		this->setKilledByAsteroid( false );
		this->setIsSuicided( false );
		this->setSeconds( 0 );

		mFragsLabel.setPosition( sf::Vector2f( 10 , 130 ) );

		std::cout << "Game restarted" << std::endl;

		pGameRestartSound->setBuffer( *pGameRestartBuffer );
		pGameRestartSound->play();

		pSprite->setPosition( sf::Vector2f( PLAYER_X_POS , PLAYER_Y_POS ) );
		pWeapon->setAmmo( AMMO );
		pWeapon->setIsOutOfAmmo( false );
		pWeapon->setShotsWep2( 0 );
		pWeapon->setWeapon( 1 );
		pWeapon->setWeapon2Temp( 0.1 );
		pWeapon->setWeaponToHot( false );

		pTimeSeconds->restart();
		pTimeMinutes->restart();

		mCanMoveUp				= true;
		mCanMoveDown			= true;
		mCanMoveLeft			= true;
		mCanMoveRight			= true;

		mCommandLock			= false;
		pCommandClock->restart();
	}

	else

	{
		std::cout << "ERROR: Restart Command Lock is still active." << std::endl;
	}
}

void Player::update( float frametime )
{
	if( mCommandLock == false )
	{
		if( pCommandClock->getElapsedTime().asSeconds() > mLockSeconds )
		{
			mCommandLock = true;
		}
	}

	/* /////////////////////////////////////////////////////////////////////////////////////////// */
	/* Command Bind Handler System (v1.0) */

	/* /////////////////////////////////////////////////////////////////////////////////////////// */

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Delete ) )
	{
		pWeapon->deleteWeapon();
	}

	/* //////////////////////////////// */ /* //////////////////////////////// */
	/* display current game time */

	if( pTimeMinutes->getElapsedTime().asMilliseconds() > 60000 )
	{
		minutes = ( minutes + 1 );
		pTimeMinutes->restart();
	}

	int seconds = pTimeSeconds->getElapsedTime().asSeconds();

	std::stringstream gse;
	gse << seconds;

	std::stringstream gm;
	gm << minutes;

	if( minutes < 10 && seconds < 10 )
	{
		mTimeRemainingLabel.setString( "Time: 0" + gm.str() + " : 0" + gse.str() );
	}

	else if( minutes > 9 && seconds < 10 )
	{
		mTimeRemainingLabel.setString( "Time: " + gm.str() + " : 0" + gse.str() ); 
	}

	else if( minutes < 10 && seconds < 10 )
	{
		mTimeRemainingLabel.setString( "Time: " + gm.str() + " : " + gse.str() );
	}

	else if( minutes < 10 && seconds > 9 )
	{
		mTimeRemainingLabel.setString( "Time: 0" + gm.str() + " : " + gse.str() );
	}

	else

	{
		mTimeRemainingLabel.setString( "Time: " + gm.str() + " : " + gse.str() );
	}

	if( pTimeSeconds->getElapsedTime().asMilliseconds() > 60000 )
	{
		pTimeSeconds->restart();
	}

	/* //////////////////////////////// */ /* //////////////////////////////// */


	if( this->getIsAlive() == true )
	{
		mStatusLabel.setColor( sf::Color::Green );
		mStatusLabel.setString( "Alive" );
	}

	if( this->getIsSuicided() == true )
	{
		mStatusLabel.setColor( sf::Color::Red );
		mStatusLabel.setString( "Suicided" );
	}

	if( this->getKilledByAsteroid() == true )
	{
		if( this->getDeaths() < 4 )
		{
			mStatusLabel.setColor( sf::Color::Red );
			mStatusLabel.setString( "Dead" );
		}

		else

		{
			mStatusLabel.setColor( sf::Color::Magenta );
			mStatusLabel.setString( "Game Over (No Lifes left)" );
		}
	}

	if( pSprite->getPosition().x < 30 )
	{
		mCanMoveLeft = false;
	}

	if( pSprite->getPosition().x > 30 )
	{
		mCanMoveLeft = true;
	}

	if( pSprite->getPosition().x > 1370 )
	{
		mCanMoveRight = false;
	}

	if( pSprite->getPosition().x < 1370 )
	{
		mCanMoveRight = true;
	}

	if( pSprite->getPosition().y < 30 )
	{
		mCanMoveUp = false;
	}

	if( pSprite->getPosition().y > 30 )
	{
		mCanMoveUp = true;
	}

	if( pSprite->getPosition().y > 870 )
	{
		mCanMoveDown = false;
	}

	if( pSprite->getPosition().y < 870 )
	{
		mCanMoveDown = true;
	}


	if( this->getPoints() == 5000 || this->getPoints() > 5000 )
	{
		this->setPoints( 0 );
		this->setLife( LIFE );
		this->setShield( SHIELD );
		this->setLevel( this->getLevel() + 1 );

		pWeapon->setAmmo( AMMO );
	}

	pSpriteLifebar->setPosition( pSprite->getPosition().x + 80 , pSprite->getPosition().y + 15 );
	pSpriteShieldbar->setPosition( pSprite->getPosition().x + 80 , pSprite->getPosition().y );

	if ( mCanMoveUp == true && this->getGameOver() == false )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::W ) )
		{
			pSprite->move( 0 , -300*frametime );
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Up ) )
		{
			pSprite->move( 0 , -300*frametime );
		}
	}

	if ( mCanMoveDown == true && this->getGameOver() == false )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::S ) )
		{
			pSprite->move( 0 , 300*frametime );
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Down ) )
		{
			pSprite->move( 0 , 300*frametime );
		}
	}

	if ( mCanMoveLeft == true && this->getGameOver() == false )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::A ) )
		{
			pSprite->move( -300*frametime , 0 );
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Left ) )
		{
			pSprite->move( -300*frametime , 0 );
		}
	}
	
	if ( mCanMoveRight == true && this->getGameOver() == false )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::D ) )
		{
			pSprite->move( 300*frametime , 0 );
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Right ) )
		{
			pSprite->move( 300*frametime , 0 );
		}
	}

	if( sf::Mouse::isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( this->getIsAlive() == true && this->getGameOver() == false )
		{
			pWeapon->fire();
		}
	}

	/* easter egg key :D */
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F ) )
	{
		if ( getShield() > 0 )
		{
			setShield( getShield() - 50*frametime );
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad8 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num9 )  )
	{
		this->suicide();
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Space ) )
	{
		this->respawn();
	}

	if( mLock == false )
	{
		if( pClock->getElapsedTime().asSeconds() > COMMAND_OVERFLOW_TIME )
		{
			mLock = true;
		}
	}

	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad9 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num0 ) )
	{
		/*if( mLock == true )
		{*/
			this->restart(); /* restart game */
		/*} */
	}

	if( mWeaponSwitchLock == false )
	{
		if( pWeaponSwitchClock->getElapsedTime().asSeconds() > WEAPON_SWITCH_WAITTIME )
		{
			mWeaponSwitchLock = true;
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad1 ) )
	{
		if( mWeaponSwitchLock == true )
		{
			this->setPlayerWeapon( 1 );

			/*

			pWeaponSwitchSound->setBuffer( *pWeaponSwitchBuffer );
			pWeaponSwitchSound->play();

			*/

			mWeaponSwitchLock = false;
			pWeaponSwitchClock->restart();
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Numpad2 ) )
	{
		if( mWeaponSwitchLock == true )
		{
			this->setPlayerWeapon( 2 );

			/*

			pWeaponSwitchSound->setBuffer( *pWeaponSwitchBuffer );
			pWeaponSwitchSound->play();

			*/

			mWeaponSwitchLock = false;
			pWeaponSwitchClock->restart();
		}
	}


	pSpriteShield->setPosition( pSprite->getPosition() );

	pSpriteShield->setColor( sf::Color( pSpriteShield->getColor().r, pSpriteShield->getColor().g, pSpriteShield->getColor().b, ( getShield() * mStep ) ) ); 

	if( getLife() == 0 || getLife() < 0 )
	{
		setIsAlive( false );
	}

	pWeapon->update( mMousePosition, getSprite().getPosition(), frametime );

	pSpriteLifebar->setTextureRect( sf::IntRect( 0 , 0 , ( mStepHP * this->getLife() ) , pTextureLifebar->getSize().y ) );
	pSpriteShieldbar->setTextureRect( sf::IntRect( 0 , 0 , ( mStepSH * this->getShield() ) , pTextureShieldbar->getSize().y ) );

	std::stringstream gs;
	gs << this->getTotalPoints();
	mGameScoreLabel.setString( "Gamescore: " + gs.str() );

	std::stringstream ls; 
	ls << this->getLevel();
	mLevelLabel.setString( "Level: " + ls.str() );

	std::stringstream cf;
	cf << this->getFrags();
	mFragsLabel.setString( "Frags: " + cf.str() );

	if( this->getIsAlive() == true )
	{
		std::stringstream posx;
		posx << pSprite->getPosition().x;
		mPosXLabel.setString( "Position [X]: " + posx.str() );

		std::stringstream posy;
		posy << pSprite->getPosition().y;
		mPosYLabel.setString( "Position [Y]: " + posy.str() );
	}


	if( pWeapon->getWeapon1() == false && pWeapon->getWeapon2() == false )
	{
		this->setGameOver( true );
		mStatusLabel.setColor( sf::Color::Magenta );
		mStatusLabel.setString( "Game Over (No Weapons left)" );
	}

	if( this->getDeaths() == 4 )
	{
		this->setGameOver( true );
	}

	if( this->getDeaths() == 4 )
	{
		mStatusLabel.setColor( sf::Color::Magenta );
		mStatusLabel.setString( "Game Over (No Lifes left)" );
	}

	if( pWeapon->getAmmo() == 0 )
	{
		pWeapon->setWeapon( 2 );
		this->setPlayerWeapon( 2 );
		pWeapon->setWeapon1( false );
	}
}

void Player::render( sf::RenderWindow *rw )
{
	/*
	* calculate mouse position
	* in relation to renderwindow( rw )
	*/
	mMousePosition = static_cast<sf::Vector2f>( sf::Mouse::getPosition( *rw ) );

	if( getIsAlive() )
	{
		pWeapon->render( rw );
		rw->draw( *pSprite );
		rw->draw( *pSpriteShield );
		rw->draw( *pSpriteLifebar );
		rw->draw( *pSpriteShieldbar );
	}

	rw->draw( mLifesLabel );
	rw->draw( mGameScoreLabel );
	rw->draw( mLevelLabel );
	rw->draw( mTimeRemainingLabel );
	rw->draw( mPosXLabel );
	rw->draw( mPosYLabel );
	rw->draw( mFragsLabel );
	rw->draw( mStatusLabel );

	if( this->getDeaths() == 0 )
	{
		rw->draw( *pSpriteH1 );
		rw->draw( *pSpriteH2 );
		rw->draw( *pSpriteH3 );
	}

	else 

	{ 
		if( this->getDeaths() == 1 ) 
		{
			rw->draw( *pSpriteH1 );
			rw->draw( *pSpriteH2 );
		}
	}

	if( this->getDeaths() == 2 )
	{
		rw->draw( *pSpriteH1 );
	}

	if( this->getGameOver() == true )
	{
		rw->draw( mGameOverLabel );
		mFragsLabel.setPosition( sf::Vector2f( 10 , 90 ) );
	}

	if( this->getIsAlive() == false )
	{
		mFragsLabel.setPosition( sf::Vector2f( 10 , 90 ) );
	}
}

void Player::handleEvents()
{

}

void Player::loadPlayer()
{

}

float Player::getPlayerPosition( sf::Vector2f position )
{
	/* get position values */
	mxpos = pSprite->getPosition().y;
	mypos = pSprite->getPosition().x;

	/* return position values */
	return mxpos;
	return mypos;
}


