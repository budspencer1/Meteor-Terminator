/*
* Filename: Security.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "security" class 
* Purpose 2: It manages all secrue trings during game
*/

/* main include guard */
#ifndef SECURITY_HPP /* ifndef = if not defined */
#define SECURITY_HPP /* define = defines not defines instance */

/* extern resources to use in program */
#include <iostream> /* controls stream in console */
#include <sstream> /* string operations libary */
#include <cstdlib> /* required for some string operations */
#include <Windows.h> /* master include for windows applications */
#include <SFML\Graphics.hpp> /* include sfml graphics libaries */
#include <SFML\Audio.hpp> /* include sfml audio libaries */

#include "Player.hpp" /* include player class */
#include "Asteroid.hpp" /* include asteroid class */

/* declares class */
class Security /* begin of class */
{

/* public ( global ) variables and commands */
public: 

	/* constructor */
	Security( Asteroid *asteroid );

	/* deconstructor */
	~Security();

	/* main global functions */
	void update( float frametime );
	void render( sf::RenderWindow *rw );
	void handleEvents();

	/* getter for private variables */
	const bool getUp()					{ return mIsInvisibleWallUp; };
	const bool getDown()				{ return mIsInvisibleWallDown; };
	const bool getRight()				{ return mIsInvisibleWallRight; };
	const bool getLeft()				{ return mIsInvisibleWallLeft; };
	const int getLifes()				{ return mLifes; };
	const bool getIsGameOver()			{ return mIsGameOver; };

	/* setter to set private variables */
	void setUp( bool Up )				{ mIsInvisibleWallUp = Up; };
	void setDown( bool Down )			{ mIsInvisibleWallDown = Down; };
	void setRight( bool Right )			{ mIsInvisibleWallRight = Right; };
	void setLeft( bool Left )			{ mIsInvisibleWallLeft = Left; };
	void setLifes( int Lifes )			{ mLifes = Lifes; };



	/* private variables ( can only be used in this-> class ) */
private:

	/* pointer for classes */
	Asteroid		*pAsteroid;

	/* invisible walls booleans */
	bool			mIsInvisibleWallUp;
	bool			mIsInvisibleWallDown;
	bool			mIsInvisibleWallRight;
	bool			mIsInvisibleWallLeft;

	/* life system */
	int				mLifes;
	bool			mIsGameOver;


}; /* end of class */

/* ends class and header */
#endif