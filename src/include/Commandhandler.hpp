/* 
* File Name: Commandhandler.hpp
* Date: 2016
* Author: Sebastian <3
* Purpose: Handle all commands for console subsystem + define class
*/

#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "Commands.inc"
#include "Version.inc"
#include "Weapon.hpp"


class CommandHandler
{


public:

	CommandHandler();
	~CommandHandler();

	void activate();
	void deactivate();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	void help();
	void about();
	void info();
	void enable_vsync( sf::RenderWindow *rw );
	void disable_vsync( sf::RenderWindow *rw );
	void enable_mousecurser( sf::RenderWindow *rw );
	void disable_mousecurser( sf::RenderWindow *rw );
	void quit();
	void suicide();
	void restart();
	void respawn();
	void outofammo( Weapon *weapon );
	void delweapon();
	void weapon1( Weapon *weapon );
	void weapon2( Weapon *weapon );
	void pause();
	void menu();
	void stats();

	void mute();

	const bool getIsPaused()			{ return mIsPaused; };
	const bool getIsOutOfAmmo()			{ return mIsOutOfAmmo; };
	const bool getIsMuted()				{ return mIsMuted; };
	const bool getIsActivated()			{ return mIsActivated; };
	const int getCommands()				{ return mCommands; };
	
	void setIsPaused( bool IsPaused )	{ mIsPaused = IsPaused; };
	void setIsOutOfAmmo( bool OOA )		{ mIsOutOfAmmo = OOA; };
	void setIsMuted( bool IsMuted )		{ mIsMuted = IsMuted; };
	void setCommands( int Commands )	{ mCommands = Commands; };
	void setIsActivated( bool Active )	{ mIsActivated = Active; };


private:

	Weapon					*pWeapon;

	sf::Clock				*pOverflowCheckClock;
	sf::Clock				*pCommandResetClock;

	bool					mIsPaused;
	bool					mIsOutOfAmmo;
	bool					mIsMuted;
	bool					mIsActivated;

	int						mCommands;


};

#endif