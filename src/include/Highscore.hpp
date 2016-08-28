/*
* File Name: Highscore.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: manage highscore
*/


#ifndef __HIGHSCORE__
#define __HIGHSCORE__

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Player.hpp"


class Highscore
{


public:

	Highscore();
	~Highscore();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	int show();

	const unsigned int getFirst()			{ return firstP; };
	const unsigned int getSecond()			{ return secondP; };
	const unsigned int getThird()			{ return thirdP; };
	const unsigned int getFourth()			{ return fourthP; };
	const unsigned int getFifth()			{ return fifthP; };
	const unsigned int getSixth()			{ return sixthP; };

	const std::string getFirstName()		{ return firstName; };
	const std::string getSecondName()		{ return secondName; };
	const std::string getThirdName()		{ return thirdName; };
	const std::string getFourthName()		{ return fourthName; };
	const std::string getFifthName()		{ return fifthName; };
	const std::string getSixthName()		{ return sixthName; };


private:

	Player					*player;
	sf::Clock				*clock;

	unsigned int			firstP;
	unsigned int			secondP;
	unsigned int			thirdP;
	unsigned int			fourthP;
	unsigned int			fifthP;
	unsigned int			sixthP;

	std::string				firstName;
	std::string				secondName;
	std::string				thirdName;
	std::string				fourthName;
	std::string				fifthName;
	std::string				sixthName;

	bool					isShowing;


};

#endif