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

#include "Engine.hpp"
#include "Player.hpp"

#include "Version.inc"
#include "Settings.inc"



Engine::Engine()
{
	std::cout << "**************************************************************" << std::endl;
	std::cout << "Welcome to " TERM_NAME " " TERM_HISTORY " " TERM_VERSION "" << std::endl;
	std::cout << "Developer: " << TERM_DEVELOPER << std::endl;
	std::cout << "Build Revision: " << TERM_REVISION << std::endl;
	std::cout << "**************************************************************" << std::endl;
	std::cout << "init: " << ENGINE << std::endl;
	std::cout << "init: " << CLOCK << std::endl;

	mIsRunning					= true;

	pRenderWindow				= new sf::RenderWindow( sf::VideoMode( RES_X , RES_Y , WINDOW_BITS ), ( TERM_NAME " - Version: " TERM_HISTORY " " TERM_VERSION " || Build: " COMPILE_DATE " // " COMPILE_TIME " || Architecture(Game): " TERM_ARCHITECTURE " || Build Revision: " TERM_REVISION "" ), sf::Style::Titlebar | sf::Style::Close );
	std::cout << "init: " << VIDEO_RENDERWINDOW << " " << VIDEOMODE << std::endl,
	pRenderWindow->setVerticalSyncEnabled( VERTICAL_SYNC_ENABLED );
	pRenderWindow->setMouseCursorVisible( MOUSE_CURSER_VISIBLE );

	/* set window icon - used in titlebar */

	pIconTexture				= new sf::Image;
	pIconTexture->loadFromFile( std::string( "media/packages/content/icons/WindowIcon.png" ) );
	pRenderWindow->setIcon( pIconTexture->getSize().x, pIconTexture->getSize().y , pIconTexture->getPixelsPtr() );

	/* ///////////////////////////////////////////// */

	pBackground					= new sf::Texture;
	pBackground->loadFromFile( std::string ( "media/packages/content/textures/ScreenBackground.bmp" ) );

	pSprite						= new sf::Sprite;
	pSprite->setTexture( *pBackground );

	pMouseTexture				= new sf::Texture;
	pMouseTexture->loadFromFile( std::string( "media/packages/content/textures/MouseCrosshair.png" ) );

	pMouseSprite				= new sf::Sprite;
	pMouseSprite->setTexture( *pMouseTexture );
	pMouseSprite->setOrigin( ( pMouseTexture->getSize().x/2 ), ( pMouseTexture->getSize().y/2 ) );
	pMouseSprite->setScale( 0.2 , 0.2 );

	pMainEvent					= new sf::Event;

	pClock						= new sf::Clock;

	pPlayer						= new Player( std::string( "media/packages/content/textures/Player.png" ), sf::Vector2f( PLAYER_X_POS , PLAYER_Y_POS ) );
	/* pAsteroid					= new Asteroid( std::string( "media/packages/content/textures/Asteroid.png" ), sf::Vector2f( 635 , -100 ) ); */
	pAsteroidManager			= new AsteroidManager();
	pCollisionSystem			= new CollisionSystem( pMouseSprite, pPlayer, pAsteroidManager->getList() );
	pCommandHandler				= new CommandHandler();

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
}


void Engine::start()
{
	while( mIsRunning == true )
	{
		CalculateFrameTime();

		render();
		update( mFrameTime );
		handleEvents();

		CommandSystem( mFrameTime );
		/* getFrameTime(); */
		quit();
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
	pPlayer->update( frametime );
	pAsteroidManager->update( frametime );
	pCollisionSystem->update( frametime );

	pMouseSprite->setPosition( static_cast<sf::Vector2f>( sf::Mouse::getPosition( *pRenderWindow ) ) );
}

void Engine::CommandSystem( float frametime )
{
	
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
	pCollisionSystem->handleEvents();
	pAsteroidManager->handleEvents();
}


void Engine::render()
{
	pRenderWindow->clear( sf::Color::Cyan );
	pRenderWindow->draw( *pSprite );
	pAsteroidManager->render( pRenderWindow );
	pPlayer->render( pRenderWindow );
	pCollisionSystem->render( pRenderWindow );
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