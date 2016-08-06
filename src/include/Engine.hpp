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
#include "Weapon.hpp"
#include "AsteroidManager.hpp"
#include "Collision.hpp"
#include "CollisionSystem.hpp"
#include "Commandhandler.hpp"
#include "EventHandler.hpp"

class Engine
{


public:

	Engine();
	~Engine();

	void start();
	void quit();

	void getWindowsVersion();
	int getArchType1();
	static char getArchType2();
	std::string getOperatingSystem();
	std::string getSystemArchitecture();


private:

	void update( float frametime );
	void handleEvents();
	void render();
	void CommandSystem();

	void CalculateFrameTime();

	sf::RenderWindow				*pRenderWindow;
	sf::Event						*pMainEvent;
	sf::Clock						*pClock;
	sf::Texture						*pBackground;
	sf::Sprite						*pSprite;

	sf::Vector2f					mMousePosition;

	sf::Texture						*pMouseTexture;
	sf::Sprite						*pMouseSprite;

	sf::Texture						*pMouseHitTexture;

	sf::Image						*pIconTexture;

	EventHandler					*pEventHandler;
	Player							*pPlayer;
	Weapon							*pWeapon;
	AsteroidManager					*pAsteroidManager;
	CollisionSystem					*pCollisionSystem;
	CommandHandler					*pCommandHandler;
	
	float							mFrameTime;
	bool							mIsRunning;



};

#endif