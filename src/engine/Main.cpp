/*
* Filename: Main.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "main" class 
* Purpose 2: It's the heart of game, it executes engine class ( main )
*/
#pragma once

#include "Engine.hpp"

#include "Settings.inc"
#include "Version.inc"

/* specify used namespaces */
using namespace sf;
using namespace std;

/* START SPLASH SCREEN AND THEN GAME */ 

int main()
{
	FreeConsole();

	static bool mIsSplash;
	mIsSplash = true;

	cout << "init: Splash Screen" << endl;
	cout << "init: Timer\n" << endl;
	cout << "Timer: 5 Seconds to Game start ...\n" << endl;

	Event *pEvent			= new Event;
	Sprite	*pSprite		= new Sprite;
	Texture	*pTexture		= new Texture;
	Font *pFont				= new Font;
	Image *pIcon			= new Image;
	Text					mCDLabel;

	pFont->loadFromFile( string( "media/packages/content/fonts/Cocogoose.otf" ) );
	pIcon->loadFromFile( string( "media/packages/content/icons/WindowIcon.png" ) );

	mCDLabel.setFont( *pFont );
	mCDLabel.setScale( 1 , 1 );

	RenderWindow *pRenderWindow				= new RenderWindow( VideoMode( RES_X , RES_Y , WINDOW_BITS ), ( TERM_NAME " | Splash Screen  - Game will start in 5 seconds ..." ) , Style::Titlebar );
	pRenderWindow->setVerticalSyncEnabled( true );
	pRenderWindow->setIcon( pIcon->getSize().x , pIcon->getSize().y , pIcon->getPixelsPtr() );

	pTexture->loadFromFile( string( "media/packages/content/textures/SplashScreen.png" ) );
	pSprite->setTexture( *pTexture );

	mCDLabel.setPosition( Vector2f( 630 , 830 ) );
	mCDLabel.setColor( Color::Green );
	mCDLabel.setString( string( "Starting in 5 Seconds ... Prepare yourself!" ) );

	pRenderWindow->clear( Color::Cyan );
	pRenderWindow->draw( *pSprite );
	pRenderWindow->draw( mCDLabel );
	pRenderWindow->display();

	Sleep( 4500 );

	pRenderWindow->close();
	mIsSplash = false;

	Sleep( 450 );

	cout << "\nStarting Game ... done\n\n\n" << endl;

	Sleep( 50 );

	Engine engine;
	engine.start();

	delete pSprite;
	delete pIcon;
	delete pRenderWindow;
	delete pEvent;
	delete pFont;

	pSprite			= nullptr;
	pIcon			= nullptr;
	pRenderWindow	= nullptr;
	pEvent			= nullptr;
	pFont			= nullptr;

	return INIT_SUCCESS;
}