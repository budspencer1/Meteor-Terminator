/*
* File Name: MenuManager.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: manage menu routines
*/


#pragma once

#ifndef MENUMANAGER___
#define MENUMANAGER___

#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>


class MenuManager
{


public:

	MenuManager();
	~MenuManager();

	virtual void updateMenu( float frametime );
	virtual void handleMenu();
	virtual void renderMenu( sf::RenderWindow *rw );


private:

	bool				isOpen;


};

#endif