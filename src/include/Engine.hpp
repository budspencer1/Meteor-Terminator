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
#include <string>
#include <fstream>
#include <sstream>
#include <SFML\Graphics.hpp>

#include "Player.hpp"
#include "Sounds.hpp"
#include "Asteroid.hpp"
#include "Weapon.hpp"
#include "AsteroidManager.hpp"
#include "Collision.hpp"
#include "CollisionSystem.hpp"
#include "Commandhandler.hpp"
#include "EventHandler.hpp"
#include "Highscore.hpp"
#include "IngameConsole.hpp"


class Engine
{


public:

	Engine();
	~Engine();

	void start();
	void quit();

	void togglePause();
	void close();

	void getWindowsVersion();
	void screenshot();
	void updateScreenShot();
	void restart();
	void updateMouse();
	void handleConsole( Console *terminal );

	void accept();
	void cancel();
	
    void CreateHighscoreEntry( Player *player , Highscore *highscore );

	float getFPS();

	int getArchType1();
	static char getArchType2();
	std::string getOperatingSystem();
	std::string getSystemArchitecture();

	bool							mIsPlaying;


private:

	void update( float frametime );
	void handleEvents();
	void render();
	void CommandSystem();

	void CalculateFrameTime();

	sf::RenderWindow				*pRenderWindow;
	sf::Event						*pMainEvent;
	sf::Clock						*pClock;
	sf::Clock						*pFPSClock;
	sf::Clock						*pFPSLockClock;
	sf::Clock						*pScreenshotClock;
	sf::Clock						*pPauseClock;
	sf::Texture						*pBackground;
	sf::Texture						*pRampageTexture;
	sf::Sprite						*pSprite;
	sf::Sprite						*pRampageSprite;
	
	sf::Texture						*pGameOverT;
	sf::Sprite						*pGameOverS;

	sf::Vector2f					mMousePosition;

	sf::Texture						*pMouseTexture;
	sf::Sprite						*pMouseSprite;

	sf::Texture						*curserT;
	sf::Texture						*pMouseHitTexture;

	sf::Image						*pIconTexture;
	sf::Text						mFPSLabel;
	sf::Text						mPauseLabel;
	sf::Font						*pFont;
	sf::Text						mName;
	sf::Text						*enterName;
	std::string						name;

	sf::RectangleShape				name_box;

	EventHandler					*pEventHandler;
	Highscore						*pHighscore;
	Player							*pPlayer;
	Sounds							*pSounds;
	Weapon							*pWeapon;
	AsteroidManager					*pAsteroidManager;
	CollisionSystem					*pCollisionSystem;
	CommandHandler					*pCommandHandler;
	Console							*pConsole;
	
	float							mFrameTime;
	bool							mIsRunning;
	bool							isPaused;
	int								mFPS;
	int								mFPSLock;
	bool							mScreenShotLock;
    double							pauseTime;
	bool							pauseLock;


};

#endif