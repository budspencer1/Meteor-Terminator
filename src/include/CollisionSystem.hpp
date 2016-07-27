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

#include "Player.hpp"
#include "Asteroid.hpp"



class CollisionSystem
{


public:

	CollisionSystem( sf::Sprite *mouse, Player *player, std::list<Asteroid*> *list );
	~CollisionSystem();

	void update( float frametime );

private:

	Player					*pPlayer;

	sf::Sprite				*pMouse;
	std::list<Asteroid*>	*pList;

	sf::SoundBuffer			*pAsteroidDestroyBuffer;
	sf::Sound				*pAsteroidDestroySound;

	sf::SoundBuffer			*pPlayerDeadBuffer;
	sf::Sound				*pPlayerDeadSound;

	bool					mPlayerCanDie;


};

#endif