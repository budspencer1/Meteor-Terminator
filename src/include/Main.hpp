#ifndef MAIN_HPP
#define MAIN_HPP

#include <Windows.h>
#include <sstream>
#include <iostream>
#include <SFML\Graphics.hpp>

class Main
{


public:

	Main();
	~Main();

	void startGame();
	void startSplash();
	void closeSplash();


private:

	sf::Clock				*pClock;
	bool					mIsSplash;
	bool					M;


};

#endif
