/*
* File Name: EventHandler.hpp
* Author: Sebastian <3
* Date: 2016
* Purpose: define "eventhandler" class + declare functions + variables
*/


#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP


#include <iostream>
#include <Windows.h>
#include <SFML\Graphics.hpp>

#include "Player.hpp"
#include "Collision.hpp"
#include "CollisionSystem.hpp"
#include "Commandhandler.hpp"
#include "Security.hpp"
#include "Weapon.hpp"


class EventHandler
{


public:

	EventHandler();
	~EventHandler();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	virtual bool onDeath();
	virtual bool onRespawn();
	virtual bool onGameStart();
	virtual bool onGameOver();
	virtual bool onSwitchWeapon();
	virtual bool onShot();
	virtual bool onFrag();
	virtual bool onWall();
	virtual bool onQuit();
	virtual bool onDelWeapon();
	virtual bool onWeaponCooldown();
	virtual bool onPickItem();
	virtual bool onCommand();
	virtual bool onCollision();
	virtual bool onSplashScreen();
	virtual bool onRestart();

	const bool getdeath()			{ return death;		};
	const bool getrespawn()			{ return respawn;	};
	const bool getgamestart()		{ return gamestart;	};
	const bool getgameover()		{ return gameover;	};
	const bool getswitchwep()		{ return switchwep;	};
	const bool getshot()			{ return shot;		};
	const bool getfrag()			{ return frag;		};
	const bool getwall()			{ return wall;		};
	const bool getquit()			{ return quit;		};
	const bool getdelwep()			{ return delwep;	};
	const bool getwepcooldown()		{ return wepcooldown;};
	const bool getpickitem()		{ return pickitem;	};
	const bool getcommand()			{ return command;	};
	const bool getcollision()		{ return collision;	};
	const bool getsplashscreen()	{ return splashscreen;};
	const bool getrestart()			{ return restart;	};

	virtual void setdeath		( bool Death  )				{ death			= Death ; };
	virtual void setrespawn		( bool Respawn )			{ respawn		= Respawn ; };
	virtual void setgamestart	( bool GameStart )			{ gamestart		= GameStart ; };
	virtual void setgameover	( bool GameOver )			{ gameover		= GameOver ; };
	virtual void setswitchwep	( bool SwitchWep )			{ switchwep		= SwitchWep ; };
	virtual void setshot		( bool Shot )				{ shot			= Shot ; };
	virtual void setfrag		( bool Frag )				{ frag			= Frag ; };
	virtual void setwall		( bool Wall )				{ wall			= Wall ; };
	virtual void setquit		( bool Quit )				{ quit			= Quit ; };
	virtual void setdelwep		( bool DelWep )				{ delwep		= DelWep ; };
	virtual void setwepcooldown	( bool WepCooldown )		{ wepcooldown	= WepCooldown ; };
	virtual void setpickitem	( bool PickItem )			{ pickitem		= PickItem ; };
	virtual void setcommand		( bool Command )			{ command		= Command ; };
	virtual void setcollision	( bool Collision )			{ collision		= Collision ; };
	virtual void setsplashscreen( bool SplashScreen )		{ splashscreen	= SplashScreen ; };
	virtual void setrestart		( bool Restart )			{ restart		= Restart ; };
	

private:

	bool			death;
	bool			respawn;
	bool			gamestart;
	bool			gameover;
	bool			switchwep;
	bool			shot;
	bool			frag;
	bool			wall;
	bool			quit;
	bool			delwep;
	bool			wepcooldown;
	bool			pickitem;
	bool			command;
	bool			collision;
	bool			splashscreen;
	bool			restart;		


};

#endif