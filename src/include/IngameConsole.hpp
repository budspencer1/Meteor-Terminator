/*
* File Name: IngameConsole.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: manage ingame console
*/


#ifndef ____CONSOLE_____
#define ____CONSOLE_____

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <sstream>

#include "Commands.inc"
#include "Version.inc"
#include "Settings.inc"
#include "Weapon.hpp"
#include "Player.hpp"
#include "Commandhandler.hpp"


class Console
{


public:

	Console();
	~Console();

	void updateConsole( float frametime , CommandHandler *cmdhan );
	void handleConsole();
	void renderConsole( sf::RenderWindow *rw );
	void getCMD();

	const sf::Event *getEvent()		{ return TextEvent; };
	const bool getIsOpen()			{ return isOpen; };

	void setIsOpen( bool Open )		{ isOpen = Open; };

	sf::Event					*TextEvent;


private:

	sf::Font					*font;
	sf::Text					inputT;
	sf::Text					outputT;

	static const bool			enableConsole = true;
	bool						isOpen;


};

#endif