/* 
* File Name: MenuManager.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: control UI classes
*/

#ifndef MENU_MANAGER_
#define MENU_MANAGER_

#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>

#include "MainMenu.hpp"


namespace GUI
{
	class MenuManager 
	{
	
	
	public:
	
		MenuManager();
		~MenuManager();
	
		void updateUI( float frametime );
		void handleUI();
		void renderUI( sf::RenderWindow *rw );
	
	
	private:
	
		bool				isOpen;
	
	
	};
}

#endif