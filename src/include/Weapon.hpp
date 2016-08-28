/*
* Filename: Weapon.hpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file defines "weapon" class 
*/


#ifndef WEAPON_HPP
#define WEAPON_HPP


#include <iostream>
#include <sstream>
#include <list>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Shot.hpp"
#include "AsteroidManager.hpp"
#include "Collision.hpp"


class Weapon
{


public:

	Weapon();
	~Weapon();

	void fire();
	void changeWeapon();
	void deleteWeapon();
	void setAmmoZero();

	bool CanHit();

	void update( sf::Vector2f position, sf::Vector2f player, float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	std::list<Shot*> *getShotList()			{ return &mList; };
	const sf::Clock &getClock()				{ return *pLockClock; };
	const sf::Text *getLabel()				{ return &mAmmoColorLabel; };
	const sf::Text *getAmmoLabel()			{ return &mAmmoLabel; };

	const int getAmmo()						{ return mAmmo; };
	const float getCooldownWep1()			{ return mCooldownWep1; };
	const float getCooldownWep2()			{ return mCooldownWep2; };
	const bool getIsOutOfAmmo()			    { return mOutOfAmmo; };
	const bool getWeaponTooHot()			{ return mWeaponTooHot; };
	const float getWeaponTemp()				{ return mWeaponTemp; };
	const int getWeapon()					{ return mWeapon; };
	const bool getWeapon1()					{ return mWeapon1; };
	const bool getWeapon2()					{ return mWeapon2; };
	const int getShotsWep2()				{ return mShotsWeapon2; };
	const float getWeapon2Temp()			{ return mWeapon2Temp; };
	const bool getWeaponLock()				{ return mWeaponLock; };
	const float getWep2TotalTemp()			{ return mWep2TotalTemp; };
	const bool getCanShoot()				{ return mCanShoot; };

	void setCooldownWep1( float Cooldown1 )	{ mCooldownWep1 = Cooldown1; };
	void setCooldownWep2( float Cooldown2 ) { mCooldownWep2 = Cooldown2; };
	void setAmmo( int Ammo )				{ mAmmo = Ammo; };
	void setIsOutOfAmmo( bool OutOfAmmo )   { mOutOfAmmo = OutOfAmmo; };
	void setWeaponToHot( bool TooHot )		{ mWeaponTooHot = TooHot; };
	void setWeaponTemp( float WeaponTemp )	{ mWeaponTemp = WeaponTemp; };
	void setWeapon( int NewWeapon )			{ mWeapon = NewWeapon; };
	void setWeapon1( bool Weapon1 )			{ mWeapon1 = Weapon1; };
	void setWeapon2( bool Weapon2 )			{ mWeapon2 = Weapon2; };
	void setShotsWep2( int ShotsWep2 )		{ mShotsWeapon2 = ShotsWep2; };
	void setWeapon2Temp( float Wep2Temp )   { mWeapon2Temp = Wep2Temp; };
	void setWeaponLock( bool WeaponLock )	{ mWeaponLock = WeaponLock; };
	void setWep2TotalTemp( float W2TT )		{ mWep2TotalTemp = W2TT; };
	void setCanShoot( bool CanShoot )		{ mCanShoot = CanShoot; };

	sf::Text					mAmmoColorLabel;
	sf::Text					mAmmoLabel;


private:


	std::list <Shot*>			mList;
	sf::Vector2f				mTarget;
	sf::Vector2f				mPlayerPosition;
	sf::Clock					*pClock1;
	sf::Clock					*pClock2;
	sf::Clock					*pLockClock;
	sf::Clock					*pWep2HotClock;

	sf::Texture					*pTexture;
	sf::Texture					*pTexture2;

	sf::SoundBuffer				*pShotSound;
	sf::Sound					*pShotPlayer;

	sf::SoundBuffer				*pOutOfAmmoBuffer;
	sf::Sound					*pOutOfAmmoSound;

	sf::SoundBuffer				*pWeaponSwitchBuffer;
	sf::Sound					*pWeaponSwitchSound;

	sf::SoundBuffer				*pShotBuffer2;
	sf::Sound					*pShotSound2;

	sf::SoundBuffer				*pCooldownBuffer;
	sf::Sound					*pCooldownSound;

	sf::Font					*pFont;

	sf::Texture					*pTextureBullet;
	sf::Sprite					*pSpriteBullet;

	sf::Sprite					*pWeaponCooldownSprite;
	sf::Texture					*pWeaponCooldownTexture;

	AsteroidManager				*pAsteroidManager;
	Shot						*pShot;

	bool						mLockWep1;
	bool						mLockWep2;

	bool						mWeaponLock;

	float						mCooldownWep1;
	float						mCooldownWep2;
	float						mWaittime;
	float						mWeapon2Temp;
	float						mWep2TotalTemp;
	float						mStepWP;
	float						mTexOriginalSizeY;					

	bool						mWeaponTooHot;
	float						mWeaponTemp;

	int							mAmmo;
	int							mAmmoWeapon2;
	int							mShotsWeapon2;

	int							mWeapon;

	bool						mWeapon1;
	bool						mWeapon2;
	bool						mCooldownWep2IfTooHot;

	bool						mOutOfAmmo;
	bool						mWeaponGotHot;
	bool						mCanShoot;


};

#endif