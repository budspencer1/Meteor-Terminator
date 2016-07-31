/*
* Filename: AsteroidManager.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "asteroidmanager" class 
*/


#ifndef ASTEROIDMANAGER_HPP
#define ASTEROIDMANAGER_HPP

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <list>
#include <stdio.h> 
#include <io.h>

#include <SFML\Graphics.hpp>
#include "Asteroid.hpp"



class AsteroidManager
{


public:

	AsteroidManager();
	~AsteroidManager();

	void insert( Asteroid *asteroid );
	void spawnAsteroid( float time );
	void checkAsteroid();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	std::list<Asteroid*> *getList() { return &mAsList; };


private:

	std::list<Asteroid*>				mAsList;
	
	sf::Clock							*pClock;


};

#endif