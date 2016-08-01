/*
* File Name: Health.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: Define and Declare "health" class
*/


#ifndef HEALTH_HPP
#define HEALTH_HPP


#include <iostream>
#include <list>
#include <Windows.h>
#include <SFML\Graphics.hpp>


class Health
{


public:

	Health( sf::Texture *texture , sf::Vector2f position , float speed , float value );
	~Health();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	const sf::Sprite &getSprite()				{ return *pSprite; };

	const bool getIsAlive()						{ return mIsAlive; };
	const float getValue()						{ return mValue; };
	const float getSpeed()						{ return mSpeed; };

	void setIsAlive( bool IsAlive )				{ mIsAlive = IsAlive; };
	void setValue( float Value )				{ mValue = Value; };
	void setSpeed( float Speed )				{ mSpeed = Speed; };


private:

	std::list <Health*>		mHealthList;
	sf::Sprite				*pSprite;

	sf::Clock				*pClock;

	bool					mIsAlive;

	float					mSpeed;
	float					mValue;


};

#endif