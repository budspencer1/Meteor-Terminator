/* 
* File Name: MainMenu.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: declare GUI classes
*/


#ifndef ___GUI___
#define	___GUI___

#include <iostream>
#include <Windows.h>
#include <math.h>
#include <SFML\Graphics.hpp>

namespace GUI
{
	class MainMenu
	{
	
	
	public:
	
		MainMenu();
		~MainMenu();
	
		void update( float frametime );
		void handle();
		void render( sf::RenderWindow *rw );
	
		const std::string &getName()	{ return *name; };

		const bool getIsMain()			{ return isMain; };
		const bool getIsHighscore()		{ return isHighscore; };
		const bool getIsQuit()			{ return isQuit; };
		const bool getIsStats()			{ return isStats; };
		const bool getIsManual()		{ return isManual; };

		virtual void setIsMain( bool Main )		{ isMain = Main; };
		virtual void setIsHighscore( bool HS )	{ isHighscore = HS; };
		virtual void setIsQuit( bool Quit )		{ isQuit = Quit; };
		virtual void setIsStats( bool Stats )   { isStats = Stats; };
		virtual void setIsManual( bool Manual )	{ isManual = Manual; };

	
	private:
	
		sf::Texture					*captionT;
		sf::Texture					*highscoreT;
		sf::Texture					*quitT;
		sf::Texture					*statsT;
		sf::Texture					*underlineT;
		sf::Texture					*manualT;

		sf::Sprite					*captionS;
		sf::Sprite					*highscoreS;
		sf::Sprite					*quitS;
		sf::Sprite					*statsS;
		sf::Sprite					*underlineS;
		sf::Sprite					*manualS;	


		bool					isEnabled;
		
		bool					isMain;
		bool					isHighscore;
		bool					isQuit;
		bool					isStats;
		bool					isManual;
		std::string				*name;

	
	};
}

#endif