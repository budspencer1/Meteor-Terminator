/*
* Filename: Asteroid.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "asteroid" class 
*/


#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <Windows.h>
#include <SFML\Graphics.hpp>



class Asteroid
{


public:

	Asteroid( std::string texturePath, sf::Vector2f position, sf::Vector2f scaleFactor, float speed, float rotationSpeed, float life );
	~Asteroid();

	void update( float frametime );
	void render( sf::RenderWindow *rw );
	void handleEvents();

	/* getter */
	const sf::Sprite &getSprite()			{ return *pSprite; };

	const int getPoints()				   { return mPoints; };
	const float getLife()				   { return mLife; } ;
	const bool getIsAlive()				   { return mIsAlive; };
	const bool getIsTarget()			   { return mIsTarget; };
	const int getItem()					   { return mItem; };
	const bool getHasItem()				   { return mHasItem; };

	/* setter */
	void setPoints( int Points )           { mPoints = Points; };
	void setLife( float Life )			   { mLife = Life; };
	void setIsAlive( bool IsAlive )		   { mIsAlive = IsAlive; };
	void setIsTarget( bool IsTarget )	   { mIsTarget = IsTarget; };
	void setItem( int Item )			   { mItem = Item; };
	void setHasItem( bool HasItem )		   { mHasItem = HasItem; };


private:

	void loadAsteroid();
	float getAsteroidPosition( sf::Vector2f position );

	/* texture variables */
	sf::Texture				*pTexture;
	sf::Sprite				*pSprite;

	sf::Texture				*pTextureTarget;

	sf::Texture				*pTextureLifeBar;
	sf::Sprite				*pSpriteLifeBar;

	float					mStep;

	float					mSpeed;
	float					mRotationSpeed;

	/* Life variables */
	int						mPoints;
	float					mLife;
	bool					mIsAlive;

	/* target variable */
	bool					mIsTarget;

	/* give asteroid armor or player life */
	int						mItem;
	bool					mHasItem;


};

#endif