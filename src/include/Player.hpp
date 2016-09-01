/*
* Filename: Player.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "player" class 
*/


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <list>
#include <SFML\Audio.hpp>

#include "Weapon.hpp"
#include "Shot.hpp"
#include "AsteroidManager.hpp"
#include "Commandhandler.hpp"


class Player
{


public:

	Player( std::string texturePath, sf::Vector2f position );
	~Player();

	void update( float frametime );
	void render( sf::RenderWindow *rw );
	void handleEvents();
	virtual void RampageMode();

	/* getter */
	const sf::Sprite &getSprite()				{ return *pSprite; };
	std::list<Shot*> *getShotList()				{ return pWeapon->getShotList(); };
	const sf::Vector2f getMousePosition()		{ return mMousePosition; };
	const sf::Text getGameOverLabel()			{ return mGameOverLabel; };


    const float getLife()								{ return mLife; };
	const bool getIsAlive()								{ return mIsAlive; };
	const int getPoints()								{ return mPoints; };
	const float getShield()								{ return mShield; };
	const int getLevel()								{ return mLevel; };
	const int getAmmo()									{ return mAmmo; };
	const bool getHasAmmo()								{ return mHasAmmo; };
	const int getDeaths()								{ return mDeaths; };
	const int getFrags()								{ return mFrags; };
	const int getShots()								{ return mShots; };
	const int getHits()									{ return mHits; };
	const bool getGameOver()							{ return mIsGameOver; };
	const int getTotalPoints()							{ return mTotalPoints; };
	const bool getIsHit()								{ return mIsHit; };
	const int getLifes()								{ return mLifes; };
	const bool getKilledByAsteroid()					{ return mKilledByAsteroid; };
	const bool getIsSuicided()							{ return mSuicided; };
	const float getSeconds()							{ return mSeconds; };
	const int getPlayerWeapon()							{ return mPlayerWeapon; };
	const bool getCommandLock()							{ return mCommandLock; };
	const int getCMDWaittime()							{ return mCommandWaittime; };
	const int getLockSeconds()							{ return mLockSeconds; };
	const bool getIsRampageMode()						{ return isRampageMode; };
	const int getRampageFrags()							{ return rampageFrags; };


	/* setter */
	virtual void setLife( float Life )							{ mLife = Life; };
	virtual void setIsAlive( bool IsAlive )						{ mIsAlive = IsAlive; };
	virtual void setPoints( int Points )						{ mPoints  = Points; };
	virtual void setShield( float Shield )						{ mShield = Shield; };
	virtual void setLevel( int Level )							{ mLevel = Level; };
	virtual void setAmmo( int Ammo )							{ mAmmo = Ammo; };
	virtual void setHasAmmo( bool HasAmmo )						{ mHasAmmo = HasAmmo; };
	virtual void setDeaths( int Deaths )						{ mDeaths = Deaths; };
	virtual void setFrags( int Frags )							{ mFrags = Frags; };
	virtual void setShots( int Shots )							{ mShots = Shots; };
	virtual void setHits( int Hits )							{ mHits = Hits; };
	virtual void setGameOver( bool GameOver )					{ mIsGameOver = GameOver; };
	virtual void setTotalPoints( int TotalPoints )				{ mTotalPoints = TotalPoints; };
	virtual void setIsHit( bool IsHit )							{ mIsHit = IsHit; };
	virtual void setLifes( int Lifes )							{ mLifes = Lifes; };
	virtual void setKilledByAsteroid( bool KbA )				{ mKilledByAsteroid = KbA; };
	virtual void setIsSuicided( bool Suicided )					{ mSuicided = Suicided; };
	virtual void setSeconds( float Seconds )					{ mSeconds = Seconds; };
	virtual void setPlayerWeapon( int PlayerWeapon )			{ mPlayerWeapon = PlayerWeapon; };
	virtual void setCommandLock( bool CommandLock )				{ mCommandLock = CommandLock; };
	virtual void setCMDWaittime( int CMDWaittime )				{ mCommandWaittime = CMDWaittime; };
	virtual void setRampageMode( bool RampageMode )				{ isRampageMode = RampageMode; };
	virtual void setRampageFrags( unsigned int RampageFrags )	{ rampageFrags = RampageFrags; };

	/* gameplay functions */
	void suicide();
	void respawn();
	void restart();
	/* ////////////////// */


private:

	void loadPlayer();

	float getPlayerPosition( sf::Vector2f position );

	/* texture variables */
	sf::Texture				*pTexture;
	sf::Sprite				*pSprite;

	sf::Texture				*pTextureH1;
	sf::Sprite				*pSpriteH1;
	sf::Texture				*pTextureH2;
	sf::Sprite				*pSpriteH2;
	sf::Texture				*pTextureH3;
	sf::Sprite				*pSpriteH3;

	sf::Texture			    *pTextureShield;
	sf::Sprite				*pSpriteShield;

	sf::Texture				*pTextureLifebar;
	sf::Sprite				*pSpriteLifebar;

	sf::Texture				*pTextureShieldbar;
	sf::Sprite				*pSpriteShieldbar;

	sf::Font				*pFont;

	sf::Text				mGameScoreLabel;

	sf::Text				mLifesLabel;

	sf::Text				mLevelLabel;

	sf::Text				mTimeRemainingLabel;
	sf::Text				mRampageTime;

	sf::Text				mPosXLabel;
	sf::Text				mPosYLabel;

	sf::Text				mFragsLabel;
	sf::Text				mStatusLabel;

	sf::Text				mGameOverLabel;

	sf::Vector2f			mMousePosition;

	sf::SoundBuffer			*pPlayerDeadBuffer;
	sf::Sound				*pPlayerDeadSound;

	sf::SoundBuffer			*pPlayerRespawnBuffer;
	sf::Sound				*pPlayerRespawnSound;

	sf::SoundBuffer			*pGameRestartBuffer;
	sf::Sound				*pGameRestartSound;

	sf::SoundBuffer			*pWeaponSwitchBuffer;
	sf::Sound				*pWeaponSwitchSound;

	sf::Clock				*pClock;
	sf::Clock				*pCommandClock;
	sf::Clock				*pTimeSeconds;
	sf::Clock				*pTimeMinutes;
	sf::Clock				*pWeaponSwitchClock;
	sf::Clock				*pRampageClock;
	sf::Clock				*pRamClockSec;

	Weapon					*pWeapon;
	AsteroidManager			*pAsteroidManager;
	CommandHandler			*pCommandHandler;

	/* invisible walls booleans */
	bool						mCanMoveLeft;
	bool						mCanMoveRight;	
	bool						mCanMoveDown;
	bool						mCanMoveUp;		

	/* Life variables */
	int						mPoints;
	int						mTotalPoints;

	float					mShield;
	float					mLife;
	int						mLifes;
	bool					mIsAlive;

	int						mStep;

	float    				mStepHP;
	float					mStepSH;

	int						mLevel;

	int						mAmmo;
	bool					mHasAmmo;

	int						mGameTime;

	bool					mIsGameOver;

	float					mxpos;
	float					mypos;

	/* score variables for game stats */
	int						mShots;
	unsigned int			mHits;
	unsigned int			mFrags;
	unsigned int			mDeaths;
	unsigned int			mCommandWaittime;
	unsigned int			minutes;

	bool					mIsHit;
	bool					mCommandLock;
	bool					mWeaponSwitchLock;

	bool					mLock;
	int						mLockSeconds;
	float					mCooldown;

	bool					mKilledByAsteroid;
	bool					mSuicided;

	float					mSeconds;
	bool					mCanSet;

	unsigned int			mPlayerWeapon;
	unsigned int			mCountdownTime;




	/* rampage mode variables */
	bool					enableRampageMode;
	bool					isRampageMode;
	unsigned int			rampageFrags;
	unsigned int			ramTime;

	sf::Text				mRampageTypeLabel;



};

#endif