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



static const unsigned int alpha    = 125;
static const unsigned int alpha2   = 200;
static const std::string ident     = "> ";
static const std::string welcomeS  = "+++ W E L C O M E   T O   M E T E O R   T E R M I N A T O R +++";
static const std::string versS     = "+++ V E R S I O N:  " TERM_DEV_AGE " " TERM_VERSION " +++\n";
static std::string cmdident		   = "";
static const std::string newline   = "\n";
static bool isVisible			   = false;

sf::Text identLabel , version , welcome;
sf::Clock *terminalClock;



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

	pConsoleSprite				= new sf::Sprite;
	pConsoleTexture				= new sf::Texture;
	pConsoleTexture->loadFromFile( std::string( "media/packages/content/textures/ConsoleBackground.png" ) );
	pConsoleSprite->setTexture( *pConsoleTexture );
	pConsoleSprite->setColor( sf::Color( pConsoleSprite->getColor().r, pConsoleSprite->getColor().g, pConsoleSprite->getColor().b, ( alpha2 + 30 ) ) );

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

	terminalClock				= new sf::Clock;
	terminalClock->restart();
	
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
	pCommand					= new Command(); 

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
	terminalIsOpen			= false;
	inputS					= "";
	outputS					= new std::string;
	isRolling				= false;

	input.setFont( *pFont );
	input.setCharacterSize( 30 );
	input.setColor( sf::Color::White );
	input.setPosition( sf::Vector2f( NULL + 45 , NULL + 260 ) );
	input.setString( std::string( inputS ) );

	output					= new sf::Text;
	output->setFont( *pFont );
	output->setCharacterSize( 30 );
	output->setColor( sf::Color::White );
	output->setPosition( sf::Vector2f( NULL + 40 , NULL + 65 ) );
	output->setString( std::string( *outputS ) );

	identLabel.setFont( *pFont );
	identLabel.setCharacterSize( 30 );
	identLabel.setColor( sf::Color::Blue );
	identLabel.setPosition( sf::Vector2f( NULL + 20 , NULL + 260 ) );
    identLabel.setString( std::string( ident ) );

	welcome.setFont( *pFont );
	welcome.setCharacterSize( 40 );
	welcome.setColor( sf::Color::Green );
	welcome.setPosition( sf::Vector2f( NULL + 60 , NULL + 5 ) );
    welcome.setString( std::string( welcomeS ) );

	version.setFont( *pFont );
	version.setCharacterSize( 30 );
	version.setColor( sf::Color::White );
	version.setPosition( sf::Vector2f( NULL + 20 , NULL + 35 ) );
    version.setString( std::string( versS ) );

	std::cout << "init: " COMMAND_SYSTEM << std::endl;
	std::cout << "init: " MAINLOOP << std::endl;
	std::cout << "init: " << "Terminal\n\n" << std::endl;
	std::cout << "init: " << "Command System" << std::endl;

	std::cout << " ------ BEGIN GAME ------ " << std::endl;
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
	delete pConsoleSprite;
	delete pConsoleTexture;
	delete terminalClock;
	delete pCommand;

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
	pConsoleSprite	 = nullptr;
	pConsoleTexture	 = nullptr;
	terminalClock	 = nullptr;
	pCommand		 = nullptr;
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
			this->handleConsole();
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
			this->handleConsole();
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
			this->handleConsole();
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
			this->handleConsole();
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

	else

	{
		std::cerr << "[ERROR]	Cannot update Highscore! (no valid name entered)" << std::endl;
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
		std::cout << " ------ END GAME ------ " << std::endl;
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
	if( terminalClock->getElapsedTime().asSeconds() > 5 )
	{
		if( isVisible )
		{
			isVisible = false;
		}
	}

	if( terminalIsOpen )
	{
		pGameOverS->setColor( sf::Color( pGameOverS->getColor().r, pGameOverS->getColor().g, pGameOverS->getColor().b, ( alpha2 + 30 ) ) );
	}

	else

	{
		pGameOverS->setColor( sf::Color( pGameOverS->getColor().r, pGameOverS->getColor().g, pGameOverS->getColor().b, alpha2 ) );
	}

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
		if( !terminalIsOpen )
		{
			pPlayer->update( frametime );
		}

		pHighscore->update( frametime );
		pSounds->update( frametime );
		pAsteroidManager->update( frametime );
		pCollisionSystem->update( frametime );
		pEventHandler->update( frametime );
	}

	pConsole->updateConsole( frametime , pCommandHandler );

	if( mIsPlaying )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::F5 ) )
		{
			if( !terminalIsOpen )
			{
				if( !isRolling )
				{
					cmdident.erase();
					inputS.erase();
					terminalIsOpen = true;
					cmdident.erase();
					inputS.erase();
				}
			}
		}

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Escape ) )
		{
			if( terminalIsOpen )
			{
				if( !isRolling )
				{
					cmdident.erase();
					inputS.erase();
					terminalIsOpen = false;
					cmdident.erase();
					inputS.erase();
				}
			}
		}
	}

	if( pPlayer->getLife() < ( LIFE / 2 ) && pPlayer->getLife() > ( LIFE / 5 ) )
	{
		pMouseSprite->setColor( sf::Color::Yellow );
	}

	else if( pPlayer->getLife() < ( LIFE / 5 ) && pPlayer->getLife() > 0 )
	{
		pMouseSprite->setColor( sf::Color::Red );
	}

	else if( pPlayer->getLife() == 0 || pPlayer->getLife() < 0 )
	{
		pMouseSprite->setColor( sf::Color::Black );
	}

	else 

	{
		pMouseSprite->setColor( sf::Color::White );
	}

	pMouseSprite->setPosition( static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) ) );
	mMousePosition = static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::P ) )
	{
		if( !terminalIsOpen )
		{
			isPaused = true;
			mIsPlaying = false;
		}
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


void Engine::console_screenshot( sf::RenderWindow *rw )
{
	sf::Image screenshot = rw->capture(); /* copy screen bytes to memory */

	std::stringstream randFileName2;
	randFileName2 << ( rand() % SCREENSHOT_LIMIT_UNSIGNED_INTEGER ); /* filename is a number between 1 and 1000000000 */

	screenshot.saveToFile( std::string( "screenshots/screenshot_ " + randFileName2.str() + ".bmp" ) ); /* save screenshot to file */
	std::cout << "Screenshot saved under 'screenshots/screenshot_" + randFileName2.str() + ".bmp'" << std::endl; /* output */ 

	output->setColor( sf::Color::White );
	cmdident = "[Screenshot]";
	*outputS = std::string( newline + "Saved Screenshot under 'screenshots/screenshot." + randFileName2.str() + ".bmp" );
	output->setString( std::string( cmdident + *outputS ) );
}


void Engine::handleConsole()
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Return ) )
	{
		if( static_cast<std::string>( input.getString() ) == "/help" )
		{
			pCommand->help( output , outputS );
		}

		else if( static_cast<std::string>( input.getString() ) == "/screenshot" )
		{
			pCommand->screenshot( pRenderWindow , output , outputS );
		}

		else if( static_cast<std::string>( input.getString() ) == "/stats" )
		{
			pCommand->stats( pPlayer , output , outputS );
		}

		isVisible = true;
		terminalClock->restart();

		cmdident.erase();
		inputS.erase();
		//this->terminalIsOpen = false;
	}
}

/* 
* old code 

void Engine::handleConsole( Console *terminal )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Return ) )
	{
		if( static_cast<std::string>( input.getString() ) == "/help" )
		{
			output.setColor( sf::Color::White );
			cmdident = "[Command Help]";
			outputS = newline + "/help /screenshot /version /stats /suicide" + newline + "/restart /respawn /quit /pause /resume" + newline + "[Command Decriptions]" + newline + "/help <command>";
			terminalClock->restart();
			isVisible = true;
			output.setString( std::string( cmdident + outputS ) );
		}

		else if( static_cast<std::string>( input.getString() ) == "/screenshot" )
		{
			this->console_screenshot( pRenderWindow );
		}

		cmdident.erase();
		inputS.erase();
		//this->terminalIsOpen = false;
	}
}

* end 
*/




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

			mName.setString( std::string( str ) );
		}

		if( !isPaused && mIsPlaying )
		{
			if( pMainEvent->type == sf::Event::TextEntered )
			{
				if( pMainEvent->text.unicode == '\b' )
				{
					if( inputS != "" )
					{
						inputS.erase( inputS.size() - 1 , 1 );
					}
				}

				else
				{
					if( pMainEvent->text.unicode < 128 )
					{
						if( ( !sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Return ) ) && ( str.size() < 20 || str.size() == 20 ) && terminalIsOpen && !isVisible )
						{
							inputS += static_cast<char>( pMainEvent->text.unicode );
						}
					}
				}
			}

			input.setString( std::string( inputS ) );
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

	if( terminalIsOpen )
	{
		pRenderWindow->draw( *pConsoleSprite );
		pRenderWindow->draw( welcome );
		if( isVisible )
		{
			pRenderWindow->draw( *output );
		}

		if( !isVisible )
		{
			pRenderWindow->draw( input );
			pRenderWindow->draw( identLabel );
		}
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