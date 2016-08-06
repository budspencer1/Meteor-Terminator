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

	bool onDeath();
	bool onRespawn();
	bool onGameStart();
	bool onGameOver();
	bool onSwitchWeapon();
	bool onShot();
	bool onFrag();
	bool onWall();
	bool onQuit();
	bool onDelWeapon();
	bool onWeaponCooldown();
	bool onPickItem();
	bool onCommand();
	bool onCollision();
	bool onSplashScreen();
	bool onRestart();

	const bool getdeath()			{ return death;		};
	const bool getrespawn()			{ return respawn;	};
	const bool getgamestart()		{ return gamestart;	};
	const bool getgameover()			{ return gameover;	};
	const bool getswitchwep()		{ return switchwep;	};
	const bool getshot()				{ return shot;		};
	const bool getfrag()				{ return frag;		};
	const bool getwall()				{ return wall;		};
	const bool getquit()				{ return quit;		};
	const bool getdelwep()			{ return delwep;	};
	const bool getwepcooldown()		{ return wepcooldown;};
	const bool getpickitem()			{ return pickitem;	};
	const bool getcommand()			{ return command;	};
	const bool getcollision()		{ return collision;	};
	const bool getsplashscreen()		{ return splashscreen;};
	const bool getrestart()			{ return restart;	};

	void setdeath		( bool Death  )				{ death			= Death ; };
	void setrespawn		( bool Respawn )				{ respawn		= Respawn ; };
	void setgamestart	( bool GameStart )			{ gamestart		= GameStart ; };
	void setgameover	( bool GameOver )			{ gameover		= GameOver ; };
	void setswitchwep	( bool SwitchWep )			{ switchwep		= SwitchWep ; };
	void setshot		( bool Shot )				{ shot			= Shot ; };
	void setfrag		( bool Frag )				{ frag			= Frag ; };
	void setwall		( bool Wall )				{ wall			= Wall ; };
	void setquit		( bool Quit )				{ quit			= Quit ; };
	void setdelwep		( bool DelWep )				{ delwep		= DelWep ; };
	void setwepcooldown	( bool WepCooldown )			{ wepcooldown	= WepCooldown ; };
	void setpickitem	( bool PickItem )			{ pickitem		= PickItem ; };
	void setcommand		( bool Command )				{ command		= Command ; };
	void setcollision	( bool Collision )			{ collision		= Collision ; };
	void setsplashscreen( bool SplashScreen )		{ splashscreen	= SplashScreen ; };
	void setrestart		( bool Restart )				{ restart		= Restart ; };
	

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