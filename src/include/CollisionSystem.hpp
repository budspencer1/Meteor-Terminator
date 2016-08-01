/*
* Filename: CollisionSystem.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "collisionsystem" class 
*/


#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP


#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>
#include <map>
#include <Windows.h>
#include <math.h>

#include "Player.hpp"
#include "Asteroid.hpp"
#include "Health.hpp"



class CollisionSystem
{


public:

	CollisionSystem( sf::Sprite *mouse, Player *player, std::list<Asteroid*> *list );
	~CollisionSystem();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	bool AsteroidHasItem();        

	const int getRandomValue()				{ return mRandomValue; };

	void setRandomValue( int RandomValue )  { mRandomValue = RandomValue; };

	std::list<Health*> *getHealthList()			{ return &mHealthList; };


private:

	Player					*pPlayer;
	Health					*pHealth;

	sf::Texture				*pTexture1;
	sf::Texture				*pTexture2;
	sf::Texture				*pTexture3;

	std::list <Health*>		mHealthList;

	sf::Sprite				*pMouse;
	std::list<Asteroid*>	*pList;

	sf::SoundBuffer			*pAsteroidDestroyBuffer;
	sf::Sound				*pAsteroidDestroySound;

	sf::SoundBuffer			*pPlayerDeadBuffer;
	sf::Sound				*pPlayerDeadSound;

	sf::SoundBuffer			*pAsteroidItemPickBuffer;
	sf::Sound				*pAsteroidItemPickSound;

	bool					mPlayerCanDie;
	int						mRandomValue;
	float					mRemainingLife;


};

#endif