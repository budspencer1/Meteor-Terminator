/*
* Filename: Engine.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "engine" class 
*/

/* open source code */

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
	#if defined( _WIN32) || defined(_WIN64) || defined(__MINGW32__ )
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
	WORD dwProcessorArchitecture;

    dwVersion = GetVersion();
 
    /* get windows version */
    dwMajorVersion = ( DWORD )( LOBYTE ( LOWORD ( dwVersion ) ) );
    dwMinorVersion = ( DWORD )( HIBYTE ( LOWORD( dwVersion ) ) );
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
	std::cout << "Developer: " << TERM_DEVELOPER << std::endl;
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
	isPaused					= false;

	mPauseLabel.setFont( *pFont );
	mPauseLabel.setColor( sf::Color( 32,178,170 ) );
	mPauseLabel.setCharacterSize( 200 );
	mPauseLabel.setPosition( sf::Vector2f( 280 , 300 ) );
	mPauseLabel.setString( std::string( "Paused" ) );

	pBackground					= new sf::Texture;
	pBackground->loadFromFile( std::string ( "media/packages/content/textures/ScreenBackground.bmp" ) );

	pSprite						= new sf::Sprite;
	pSprite->setTexture( *pBackground );

	pMouseTexture				= new sf::Texture;
	pMouseTexture->loadFromFile( std::string( "media/packages/content/textures/MouseCrosshair.png" ) );

	pMouseHitTexture			= new sf::Texture;
	pMouseHitTexture->loadFromFile( std::string( "media/packages/content/textures/MouseHitCrosshair.png" ) );

	pMouseSprite				= new sf::Sprite;
	pMouseSprite->setTexture( *pMouseTexture );
	pMouseSprite->setOrigin( ( pMouseTexture->getSize().x/2 ), ( pMouseTexture->getSize().y/2 ) );
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

	pPlayer						= new Player( std::string( "media/packages/content/textures/Player.png" ), sf::Vector2f( PLAYER_X_POS , PLAYER_Y_POS ) );
	/* pAsteroid					= new Asteroid( std::string( "media/packages/content/textures/Asteroid.png" ), sf::Vector2f( 635 , -100 ) ); */
	pAsteroidManager			= new AsteroidManager();
	pCollisionSystem			= new CollisionSystem( pMouseSprite, pPlayer, pAsteroidManager->getList() );
	pCommandHandler				= new CommandHandler();
	pEventHandler				= new EventHandler();
	pWeapon						= new Weapon();

	mMousePosition			= sf::Vector2f( 0 , 0 );
	mFPSLock				= 500;
	mScreenShotLock			= true;

	std::cout << "init: " COMMAND_SYSTEM << std::endl;
	std::cout << "init: " MAINLOOP << std::endl;
	std::cout << "" << std::endl;

	Sleep( 1000 );
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
}


void Engine::screenshot()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F12 ) )
	{
		if( mScreenShotLock == true )
		{
			sf::Image screenshot = pRenderWindow->capture(); /* copy screen bytes to memory */

			std::stringstream randFileName;
			randFileName << ( rand() % SCREENSHOT_LIMIT_UNSIGNED_INTEGER ); /* filename is a number between 1 and 1000000000 */

			screenshot.saveToFile( std::string( "screenshots/screenshot_" + randFileName.str() + ".bmp" ) ); /* save screenshot to file */

			std::cout << "Screenshot saved under screenshots/screenshot_" + randFileName.str() + ".bmp" << std::endl; /* output */

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
	while( mIsRunning == true )
	{
		if( isPaused == false )
		{
			this->getFPS();
			this->CalculateFrameTime();

			this->render();
			this->update( mFrameTime );

			this->handleEvents();
			this->quit();

			this->CommandSystem();
			this->pause();
			this->screenshot();
			this->updateScreenShot();
			/* getFrameTime(); */
		}

		else

		{
			this->getFPS();
			this->render();
			this->handleEvents();
			this->CalculateFrameTime();
			
			this->resume();
			this->screenshot();
			this->updateScreenShot();
		}
	}
}


void Engine::pause()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::P ) )
	{
		if( isPaused == false )
		{
			isPaused = true;
		}
	}
}


void Engine::resume()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::R ) )
	{
		if( isPaused == true )
		{
			isPaused = false;
		}
	}
}


void Engine::quit()
{
	if( mIsRunning	== false )
	{
		std::cout << "" << std::endl;
		std::cout << " ------ END GAME LOG ------ " << std::endl;
		std::cout << "Closing Application ... done" << std::endl;
		Sleep( 300 );
		pRenderWindow->close();
	}
}


void Engine::update( float frametime )
{
	std::stringstream fps;
	fps << mFPS;

	if( pFPSLockClock->getElapsedTime().asMilliseconds() > mFPSLock )
	{
		mFPSLabel.setString( "FPS:			   " + fps.str() );
		pFPSLockClock->restart();
	}

	pPlayer->update( frametime );
	pAsteroidManager->update( frametime );
	pCollisionSystem->update( frametime );
	pEventHandler->update( frametime );


	if( pCollisionSystem->getIsHit() == true )
	{
		pMouseSprite->setTexture( *pMouseHitTexture );
	}

	else

	{
		pMouseSprite->setTexture( *pMouseTexture );
	}

	pMouseSprite->setPosition( static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) ) );
	mMousePosition = static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::P ) )
	{
		isPaused = true;
	}
}


void Engine::CommandSystem()
{
	
}


float Engine::getFPS()
{
	float lastFPS = 0;

	float currentTime = pFPSClock->restart().asSeconds();
	float fps = 1.f / ( currentTime - lastFPS );

	mFPS = fps;

	return mFPS;
}


void Engine::handleEvents()
{
	while( pRenderWindow->pollEvent( *pMainEvent ) )
	{
		if( pMainEvent->type == sf::Event::Closed )
		{
			mIsRunning = false;
		}
	}

	pPlayer->handleEvents();
	pWeapon->handleEvents();
	pCollisionSystem->handleEvents();
	pAsteroidManager->handleEvents();
	pEventHandler->handleEvents();
}


void Engine::render()
{
	pRenderWindow->clear( sf::Color::Cyan );
	pRenderWindow->draw( *pSprite );
	pAsteroidManager->render( pRenderWindow );
	pPlayer->render( pRenderWindow );
	pCollisionSystem->render( pRenderWindow );
	pEventHandler->render( pRenderWindow );
	pRenderWindow->draw( *pMouseSprite );
	pRenderWindow->draw( mFPSLabel );

	if( isPaused == true )
	{
		pRenderWindow->draw( mPauseLabel );
	}

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