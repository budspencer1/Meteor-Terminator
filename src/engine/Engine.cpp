/*
* Filename: Engine.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "engine" class 
*/

/* open source code */
#pragma once 

#pragma warning( disable: 4244 )
#pragma warning( disable: 4305 )

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Config.hpp>
#include <SFML\Network.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <array>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <list>
#include <cstdio>
#include <string.h>
#include <winapifamily.h>

#include "Engine.hpp"
#include "Player.hpp"

#include "Version.inc"
#include "Settings.inc"


std::string Engine::getOperatingSystem()
{
	#if defined( _WIN32 ) || defined( _WIN64 ) || defined( __MINGW32__ )
	    return "Windows (32 Bit)";
	#elif defined( __linux__ )
	    return "Linux";
	#elif defined( __FreeBSD__ )
	    return "FreeBSD";
	#elif defined( BSD )
	    return "BSD";
	#elif defined( __sun )
	return "Solaris";
	#elif defined( __APPLE__ )
	    return "Mac OS X";
	#else
	    return "Unknown Operating System";
	#endif
}

void Engine::getWindowsVersion()
{
	DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
 
    /* get windows version */
    dwMajorVersion = ( DWORD )( LOBYTE ( LOWORD ( dwVersion ) ) );
    dwMinorVersion = ( DWORD )( HIBYTE ( LOWORD ( dwVersion ) ) );
	/* /////////////////////////////////////////////////////// */

    /* get windows build number */
    if ( dwVersion < 0x80000000 )              
        dwBuild = ( DWORD )( HIWORD ( dwVersion ) );
	/* /////////////////////////////////////////////////////// */

	printf( "Windows Version: %d.%d (Build: %d)\n", dwMajorVersion , dwMinorVersion , dwBuild );
}

Engine::Engine()
{
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Welcome to " TERM_NAME " " TERM_DEV_AGE " " TERM_VERSION "" << std::endl;
	std::cout << "Programming: " << TERM_DEVELOPER << std::endl;
	std::cout << "Build Revision: " << TERM_REVISION << std::endl;
	this->getWindowsVersion();
	std::cout << "**************************************************************" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "init: " << ENGINE << std::endl;
	std::cout << "init: " << CLOCK << std::endl;

	pRenderWindow				= new sf::RenderWindow( sf::VideoMode( RES_X , RES_Y , WINDOW_BITS ), ( TERM_NAME " - Version: " TERM_DEV_AGE " " TERM_VERSION " || Build: " COMPILE_DATE " // " COMPILE_TIME " || Build Revision: " TERM_REVISION " || Game Build Architecture: " + this->getOperatingSystem() + "" ), sf::Style::Titlebar | sf::Style::Close );
	std::cout << "init: " << VIDEO_RENDERWINDOW << " " << VIDEOMODE << std::endl,
	pRenderWindow->setVerticalSyncEnabled( VERTICAL_SYNC_ENABLED );
	pRenderWindow->setMouseCursorVisible( MOUSE_CURSER_VISIBLE );

	pFont						= new sf::Font;
	pFont->loadFromFile( std::string( "media/packages/content/fonts/Cocogoose.otf" ) );

	mFPSLabel.setFont( *pFont );
	mFPSLabel.setScale( 0.4 , 0.4 );
	mFPSLabel.setColor( sf::Color::White );
	mFPSLabel.setPosition( sf::Vector2f( 1250 , 830 ) );

	/* set window icon - used in titlebar */

	pIconTexture				= new sf::Image;
	pIconTexture->loadFromFile( std::string( "media/packages/content/icons/WindowIcon.png" ) );
	pRenderWindow->setIcon( pIconTexture->getSize().x, pIconTexture->getSize().y , pIconTexture->getPixelsPtr() );

	/* ///////////////////////////////////////////// */
	mIsRunning					= true;
	mIsPlaying					= false;
	isPaused					= false;
	static const unsigned int alpha    = 125;
	static const unsigned int alpha2   = 200;

	mPauseLabel.setFont( *pFont );
	mPauseLabel.setColor( sf::Color( 32 , 178 , 170 ) );
	mPauseLabel.setCharacterSize( 200 );
	mPauseLabel.setPosition( sf::Vector2f( 280 , 300 ) );
	mPauseLabel.setString( std::string( "Paused" ) );

	pBackground					= new sf::Texture;
	pBackground->loadFromFile( std::string ( "media/packages/content/textures/ScreenBackground.bmp" ) );

	pSprite						= new sf::Sprite;
	pSprite->setTexture( *pBackground );

	pRampageSprite				= new sf::Sprite;
	pRampageTexture				= new sf::Texture;
	pRampageTexture->loadFromFile( std::string( "media/packages/content/textures/Red.png" ) );
	pRampageSprite->setTexture( *pRampageTexture );
	pRampageSprite->setColor( sf::Color( pRampageSprite->getColor().r, pRampageSprite->getColor().g, pRampageSprite->getColor().b, alpha ) );

	pMouseTexture				= new sf::Texture;
	pMouseTexture->loadFromFile( std::string( "media/packages/content/textures/MouseCrosshair.png" ) );

	pMouseHitTexture			= new sf::Texture;
	pMouseHitTexture->loadFromFile( std::string( "media/packages/content/textures/MouseHitCrosshair.png" ) );

	pGameOverS					= new sf::Sprite;
	pGameOverT					= new sf::Texture;
	pGameOverT->loadFromFile( std::string( "media/packages/content/textures/Paused.png" ) );
	pGameOverS->setTexture( *pGameOverT );
	pGameOverS->setColor( sf::Color( pGameOverS->getColor().r, pGameOverS->getColor().g, pGameOverS->getColor().b, alpha2 ) );

	pMouseSprite				= new sf::Sprite;
	pMouseSprite->setTexture( *pMouseTexture );
	pMouseSprite->setOrigin( ( pMouseTexture->getSize().x / 2 ), ( pMouseTexture->getSize().y / 2 ) );
	pMouseSprite->setScale( 0.1 , 0.1 );

	pMainEvent					= new sf::Event;

	pClock						= new sf::Clock;
	pClock->restart();

	pFPSClock					= new sf::Clock;
	pFPSClock->restart();

	pFPSLockClock				= new sf::Clock;
	pFPSLockClock->restart();

	pScreenshotClock			= new sf::Clock;
	pScreenshotClock->restart();

	pPauseClock					= new sf::Clock;
	pPauseClock->restart();
	
	name_box.setOutlineThickness( 4 );
	name_box.setOutlineColor( sf::Color::White );
	name_box.setFillColor( sf::Color::Transparent );
	name_box.setSize( sf::Vector2f( 400 , 40 ) );
	name_box.setOrigin( sf::Vector2f( 200 , 20 ) );
	name_box.setPosition( sf::Vector2f( RES_X / 2 , RES_Y / 2 ) );

	pPlayer						= new Player( std::string( "media/packages/content/textures/Player.png" ) , sf::Vector2f( PLAYER_X_POS , PLAYER_Y_POS ) );
	/* pAsteroid					= new Asteroid( std::string( "media/packages/content/textures/Asteroid.png" ), sf::Vector2f( 635 , -100 ) ); */
	pAsteroidManager			= new AsteroidManager();
	pCollisionSystem			= new CollisionSystem( pMouseSprite , pPlayer , pAsteroidManager->getList() );
	pCommandHandler				= new CommandHandler();
	pEventHandler				= new EventHandler();
	pWeapon						= new Weapon();
	pSounds						= new Sounds( pPlayer );
	pHighscore					= new Highscore();
	pConsole					= new Console();

	std::ifstream nameS;
	nameS.open( std::string( "src/script/Name.nm" ) );
	std::string name;
	nameS >> name;

	while( name.size() > 12 )
	{
		name.erase( name.size() - 1 , 1 );
	}

	mName.setFont( *pFont );
	mName.setCharacterSize( 30 );
	mName.setColor( sf::Color::Green );
	mName.setPosition( sf::Vector2f( ( RES_X / 2 ) - 180 , ( RES_Y / 2 ) - 19 ) );
	mName.setString( std::string( name ) );

	enterName				= new sf::Text;
	enterName->setFont( *pFont );
	enterName->setCharacterSize( 30 );
	enterName->setColor( sf::Color::White );
	enterName->setPosition( sf::Vector2f( ( RES_X / 2 ) - 450 , ( RES_Y / 2 ) - 19 ) );
	enterName->setString( std::string( "Enter Name: " ) );

	mMousePosition			= sf::Vector2f( RES_X / 2 , RES_Y / 2 );
	mFPSLock				= 500;
	mScreenShotLock			= true;
	pauseLock				= true;
	pauseTime				= 0.25;

	std::cout << "init: " COMMAND_SYSTEM << std::endl;
	std::cout << "init: " MAINLOOP << std::endl;
	std::cout << "" << std::endl;

	std::cout << "" << std::endl;
	std::cout << " ------ BEGIN GAME LOG ------ " << std::endl;
	std::cout << "" << std::endl;
	/* std::cout << "Game started. Waiting for Commands. Do #help to display command list." << std::endl; */
	std::cout << "" << std::endl;
}


Engine::~Engine()
{
	delete pRenderWindow;
	delete pMainEvent;
	delete pClock;
	delete pBackground;
	delete pSprite;
	delete pPlayer;
	delete pAsteroidManager;
	delete pMouseTexture;
	delete pMouseSprite;
	delete pCommandHandler;
	delete pMouseHitTexture;
	delete pEventHandler;
	delete pFont;
	delete pFPSClock;
	delete pFPSLockClock;
	delete pScreenshotClock;
	delete pRampageSprite;
	delete pRampageTexture;
	delete pHighscore;
	delete pGameOverS;
	delete pGameOverT;
	delete pPauseClock;
	delete enterName;
	delete pConsole;

	pRenderWindow    = nullptr;
	pMainEvent	     = nullptr;
	pClock           = nullptr;		
	pBackground      = nullptr;		
	pSprite	         = nullptr;		
	pPlayer	         = nullptr;		
	pAsteroidManager = nullptr;
	pMouseTexture    = nullptr;
	pMouseTexture    = nullptr;
	pCommandHandler  = nullptr;
	pMouseHitTexture = nullptr;
	pEventHandler    = nullptr;
	pFont			 = nullptr;
	pFPSClock		 = nullptr;
	pFPSLockClock	 = nullptr;
	pScreenshotClock = nullptr;
	pRampageSprite	 = nullptr;
	pRampageTexture	 = nullptr;
	pHighscore		 = nullptr;
	pGameOverS		 = nullptr;
	pGameOverT		 = nullptr;
	pPauseClock		 = nullptr;
	enterName		 = nullptr;
	pConsole		 = nullptr;
}

std::string str;

void Engine::screenshot()
{
	std::string time = __TIME__;
	std::string date = __DATE__;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F12 ) )
	{
		if( mScreenShotLock == true )
		{
			sf::Image screenshot = pRenderWindow->capture(); /* copy screen bytes to memory */

			std::stringstream randFileName;
			randFileName << ( rand() % SCREENSHOT_LIMIT_UNSIGNED_INTEGER ); /* filename is a number between 1 and 1000000000 */

			screenshot.saveToFile( std::string( "screenshots/screenshot_ " + randFileName.str() + ".bmp" ) ); /* save screenshot to file */
			std::cout << "Screenshot saved under 'screenshots/screenshot_" + randFileName.str() + ".bmp'" << std::endl; /* output */ 

			mScreenShotLock = false;
		}
	}
}


void Engine::updateScreenShot()
{
	if( mScreenShotLock == false && pScreenshotClock->getElapsedTime().asSeconds() > SCREENSHOT_LOCK_TIME_IN_SECONDS_UNSIGNED_INT )
	{
		mScreenShotLock = true;
		pScreenshotClock->restart();
	}
}


void Engine::start()
{
	while( mIsRunning )
	{
		if( !mIsPlaying )
		{
			this->handleConsole( pConsole );
			this->togglePause();
			this->update( mFrameTime );
			this->render();
			this->handleEvents();
			this->CalculateFrameTime();
			this->getFPS();
			this->screenshot();
			this->close();

			this->quit();
		}

		else

		if( !isPaused && !pPlayer->getGameOver() )
		{
			this->handleConsole( pConsole );
			this->togglePause();
			this->restart();
			this->close();

			this->getFPS();
			this->CalculateFrameTime();

			this->render();
			this->update( mFrameTime );

			this->handleEvents();
			this->quit();

			this->CommandSystem();
			this->screenshot();
			this->updateScreenShot();
			/* getFrameTime(); */
		}

		else if( isPaused && !pPlayer->getGameOver() )

		{
			this->handleConsole( pConsole );
			this->update( mFrameTime );
			this->togglePause();
			this->restart();
			this->close();
			this->getFPS();
			this->render();
			this->handleEvents();
			this->CalculateFrameTime();
			
			this->screenshot();
			this->updateScreenShot();
			this->quit();
		}

		else if( pPlayer->getGameOver() )
		{
			this->handleConsole( pConsole );
			this->CreateHighscoreEntry( pPlayer , pHighscore );
			this->update( mFrameTime );
			this->togglePause();
			this->restart();
			this->render();
			this->close();
			this->handleEvents();
			this->screenshot();
			this->quit();
		}
	}
}


void Engine::restart()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F3 ) )
	{
		pPlayer->restart();
	}
}


void Engine::CreateHighscoreEntry( Player *player , Highscore *highscore )
{
	if( static_cast<std::string>( mName.getString() ) != "" )
	{
		std::ofstream highscoreS;
		highscoreS.open( std::string( "src/script/Highscore.hs" ) );

		const int p = player->getPoints();
		const std::string nm = static_cast<std::string>( mName.getString() );
		std::string n = "\n";

		if( player->getPoints() > highscore->getFirst() )
		{
			highscoreS << p << n << highscore->getSecond() << n << highscore->getThird() << n << highscore->getFourth() << n << highscore->getFifth() << n << highscore->getSixth() << n << nm << n << highscore->getSecondName() << n << highscore->getThirdName() << n << highscore->getFourthName() << n << highscore->getFifthName() << n << highscore->getSixthName();
			highscoreS.close();
		}

		else if ( player->getPoints() > highscore->getSecond() && player->getPoints() < highscore->getFirst() )

		{
			highscoreS << highscore->getFirst() << n << p << n << highscore->getThird() << n << highscore->getFourth() << n << highscore->getFifth() << n << highscore->getSixth() << n << highscore->getFirstName() << n << nm << n << highscore->getThirdName() << n << highscore->getFourthName() << n << highscore->getFifthName() << n << highscore->getSixthName();
			highscoreS.close();
		}

		else if ( player->getPoints() > highscore->getThird() && player->getPoints() < highscore->getSecond() )

		{
			highscoreS << highscore->getFirst() << n << highscore->getSecond() << n << p << n << highscore->getFourth() << n << highscore->getFifth() << n << highscore->getSixth() << n << highscore->getFirstName() << n << highscore->getSecondName() << n << nm << n << highscore->getFourthName() << n << highscore->getFifthName() << n << highscore->getSixthName();
			highscoreS.close();
		}

		else if ( player->getPoints() > highscore->getFourth() && player->getPoints() < highscore->getThird() )

		{
			highscoreS << highscore->getFirst() << n << highscore->getSecond() << n << highscore->getThird() << n << p << n << highscore->getFifth() << n << highscore->getSixth() << n << highscore->getFirstName() << n << highscore->getSecondName() << n << highscore->getThirdName() << n << nm << n << highscore->getFifthName() << n << highscore->getSixthName();
			highscoreS.close();
		}

		else if ( player->getPoints() > highscore->getFifth() && player->getPoints() < highscore->getFourth() )

		{
			highscoreS << highscore->getFirst() << n << highscore->getSecond() << n << highscore->getThird() << n << highscore->getFourth() << n << p << n << highscore->getSixth() << n << highscore->getFirstName() << n << highscore->getSecondName() << n << highscore->getThirdName() << n << highscore->getFourthName() << n << nm << n << highscore->getSixthName();
			highscoreS.close();
		}

		else if ( player->getPoints() > highscore->getSixth() && player->getPoints() < highscore->getFifth() )

		{
			highscoreS << highscore->getFirst() << n << highscore->getSecond() << n << highscore->getThird() << n << highscore->getFourth() << n << highscore->getFifth() << n << p << n << highscore->getFirstName() << n << highscore->getSecondName() << n << highscore->getThirdName() << n << highscore->getFourthName() << n << highscore->getFifthName() << n << nm;
			highscoreS.close();
		}

		else 

		{
			highscoreS << highscore->getFirst() << n << highscore->getSecond() << n << highscore->getThird() << n << highscore->getFourth() << n << highscore->getFifth() << n << highscore->getSixth() << n << highscore->getFirstName() << n << highscore->getSecondName() << n << highscore->getThirdName() << n << highscore->getFourthName() << n << highscore->getFifthName() << n << highscore->getSixthName();
			highscoreS.close();
		}
	}
}


void Engine::togglePause()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Pause ) )
	{
		if( !isPaused || !!mIsPlaying )
		{
			if( pauseLock )
			{
				isPaused = true;
				mIsPlaying = false;
				pauseLock = false;
				pPauseClock->restart();
			}
		}

		else if( isPaused || !mIsPlaying )
		{
			if( pauseLock )
			{
				isPaused = false;
				mIsPlaying = true;
				pauseLock = false;
				pPauseClock->restart();
			}
		}
	}
}


void Engine::close()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::End ) )
	{
		mIsRunning = false;
	}
}


void Engine::quit()
{
	if( mIsRunning	== false )
	{
		std::cout << "" << std::endl;
		std::cout << " ------ END GAME LOG ------ " << std::endl;
		std::cout << "Closing Application ... done" << std::endl;

		std::ofstream nameS2;
		nameS2.open( std::string( "src/script/Name.nm" ) );
		nameS2 << static_cast<std::string>( mName.getString() );
		nameS2.close();
		this->CreateHighscoreEntry( pPlayer , pHighscore );


		Sleep( 300 );
		pRenderWindow->close();
	}
}


void Engine::update( float frametime )
{
	if( str.size() > 12 )
	{
		str.size() - ( 1 , 1 );
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F8 ) )
	{
		if( !mIsPlaying )
		{
			mIsPlaying = true;
		}
	}

	if( !pauseLock )
	{
		if( pPauseClock->getElapsedTime().asSeconds() > pauseTime )
		{
			pauseLock = true;
			pPauseClock->restart();
		}
	}

	if( pCollisionSystem->getIsHit() == true )
	{
		pMouseSprite->setTexture( *pMouseHitTexture );
	}

	else

	{
		pMouseSprite->setTexture( *pMouseTexture );
	}

	std::stringstream fps;
	fps << mFPS;

	if( pFPSLockClock->getElapsedTime().asMilliseconds() > mFPSLock )
	{
		mFPSLabel.setString( "FPS:			   " + fps.str() );
		pFPSLockClock->restart();
	}

	if( mIsPlaying )
	{
		pPlayer->update( frametime );
		pHighscore->update( frametime );
		pSounds->update( frametime );
		pAsteroidManager->update( frametime );
		pCollisionSystem->update( frametime );
		pEventHandler->update( frametime );
	}

	pConsole->updateConsole( frametime , pCommandHandler );


	if( pPlayer->getLife() < ( LIFE / 2 ) && pPlayer->getLife() > ( LIFE / 5 ) )
	{
		pMouseSprite->setColor( sf::Color::Yellow );
	}

	else if( pPlayer->getLife() < ( LIFE / 5 ) )
	{
		pMouseSprite->setColor( sf::Color::Red );
	}

	else

	{
		pMouseSprite->setColor( sf::Color::White );
	}

	pMouseSprite->setPosition( static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) ) );
	mMousePosition = static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::P ) )
	{
		isPaused = true;
		mIsPlaying = false;
	}
}


void Engine::CommandSystem()
{
	
}


float Engine::getFPS()
{
	float lastFPS = 0;

	float currentTime = pFPSClock->restart().asSeconds();
	float fps = ( 1.f / ( currentTime - lastFPS ) );

	mFPS = fps;

	return mFPS;
}


static std::string getName()
{
	return str;
}


void Engine::handleConsole( Console *terminal )
{
	while( pRenderWindow->pollEvent( *pConsole->TextEvent ) )
	{
		pConsole->handleConsole();
	}
}


void Engine::handleEvents()
{
	while( pRenderWindow->pollEvent( *pMainEvent ) )
	{
		if( pMainEvent->type == sf::Event::Closed )
		{
			mIsRunning = false;
		}

		if( pPlayer->getGameOver() || !mIsPlaying || isPaused )
		{
			if( pMainEvent->type == sf::Event::TextEntered )
			{
				if( pMainEvent->text.unicode == '\b' )
				{
					if( str != "" )
					{
						str.erase( str.size() - 1 , 1 );
					}
				}

				else
				{
					if( pMainEvent->text.unicode < 128 )
					{
						if( ( !sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Space ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Return ) ) && ( str.size() < 12 || str.size() == 12 ) )
						{
							str += static_cast<char>( pMainEvent->text.unicode );
						}
					}
				}
			}

			mName.setString( str );
		}
	}

	pPlayer->handleEvents();
	pHighscore->handleEvents();
	pSounds->handleEvents();
	pWeapon->handleEvents();
	pCollisionSystem->handleEvents();
	pAsteroidManager->handleEvents();
	pEventHandler->handleEvents();
}


void Engine::render()
{
	pRenderWindow->clear( sf::Color::Cyan );
	pRenderWindow->draw( *pSprite );

	if( pPlayer->getIsRampageMode() )
	{
		pRenderWindow->draw( *pRampageSprite );
	}

	pAsteroidManager->render( pRenderWindow );
	pPlayer->render( pRenderWindow );
	pSounds->render( pRenderWindow );
	pCollisionSystem->render( pRenderWindow );
	pEventHandler->render( pRenderWindow );
	pHighscore->render( pRenderWindow );
	pConsole->renderConsole( pRenderWindow );

	pRenderWindow->draw( mFPSLabel );

	if( pPlayer->getGameOver() )
	{
		pRenderWindow->draw( pPlayer->getGameOverLabel() );
	}

	if( pPlayer->getGameOver() || !mIsPlaying || isPaused )
	{
		pRenderWindow->draw( *pGameOverS );
		pRenderWindow->draw( name_box );
		pRenderWindow->draw( *enterName );
		pRenderWindow->draw( mName );
	}

	pRenderWindow->draw( *pMouseSprite );
	pRenderWindow->display();
}


void Engine::CalculateFrameTime()
{
	mFrameTime = pClock->getElapsedTime().asSeconds();
	pClock->restart();

	/*
	std::cout << "Frametime: " << mFrameTime << std::endl;
	return mFrameTime;
	*/
}