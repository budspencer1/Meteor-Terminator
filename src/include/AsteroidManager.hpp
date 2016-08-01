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

	bool hasItem();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	const sf::Sprite &getSprite()			{ return *pHealthSprite; };
	const bool getHealthIsAlive()			{ return mHealthIsAlive; };
	const float getItemCalc()				{ return mItemCalc; };
	std::list<Asteroid*> *getList()			{ return &mAsList; };	

	void setHealthIsAlive( bool HIA )		{ mHealthIsAlive = HIA; };
	void setItemCalc( float ItemCalc )		{ mItemCalc = ItemCalc; };


private:

	std::list<Asteroid*>				mAsList;
	
	sf::Clock							*pClock;

	sf::Texture							*pHealthTexture;
	sf::Sprite							*pHealthSprite;

	float								mItemCalc;
	int									mGetItem;
	bool								mHealthIsAlive;

};

#endif