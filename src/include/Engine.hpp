/*
* Filename: Engine.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "engine" class 
*/


#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "Player.hpp"
#include "Asteroid.hpp"
#include "AsteroidManager.hpp"
#include "Collision.hpp"
#include "CollisionSystem.hpp"
#include "Commandhandler.hpp"

class Engine
{


public:

	Engine();
	~Engine();

	void start();
	void quit();


private:

	void update( float frametime );
	void handleEvents();
	void render();
	void CommandSystem( float frametime );

	void CalculateFrameTime();

	sf::RenderWindow				*pRenderWindow;
	sf::Event						*pMainEvent;
	sf::Clock						*pClock;
	sf::Texture						*pBackground;
	sf::Sprite						*pSprite;

	sf::Texture						*pMouseTexture;
	sf::Sprite						*pMouseSprite;

	sf::Image						*pIconTexture;

	Player							*pPlayer;
	AsteroidManager					*pAsteroidManager;
	CollisionSystem					*pCollisionSystem;
	CommandHandler					*pCommandHandler;
	
	float							mFrameTime;
	bool							mIsRunning;



};

#endif