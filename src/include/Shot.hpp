/*
* Filename: Shot.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "shot" class 
* Purpose #2: To send engine the mouse pointer position
*/


#ifndef SHOT_HPP
#define SHOT_HPP


#include <iostream>
#include <io.h>
#include <SFML\Graphics.hpp>
#include <Windows.h>


class Shot
{


public:

	Shot( sf::Vector2f direction, sf::Vector2f position, sf::Texture *texture );
	~Shot();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	const sf::Sprite &getSprite()		    { return *pSprite; };
	const sf::Vector2f &getVector()         { return mDirection; };
	const sf::Clock &getClock()				{ return *pClock; };

	const bool getIsAlive()			        { return mIsAlive; };
	const float getShotSpeed()				{ return mSpeed; };
	
	void setIsAlive( bool IsAlive )			{ mIsAlive = IsAlive; }; 
	void setSpeed( float Speed )			{ mSpeed = Speed; };


private:

	sf::Vector2f				mDirection;
	sf::Clock					*pClock;
	sf::Sprite					*pSprite;

	bool						mIsAlive;
	float						mSpeed;


};

#endif