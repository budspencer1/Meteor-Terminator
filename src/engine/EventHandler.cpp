/*
* File Name: EventHandler.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: define "eventhandler" class functions
*/

#include "EventHandler.hpp"


EventHandler::EventHandler()
{
	this->setdeath			( false );
	this->setrespawn		( false );
	this->setgamestart		( false );
	this->setgameover		( false );
	this->setswitchwep		( false );
	this->setshot			( false );
	this->setfrag			( false );
	this->setwall			( false );
	this->setquit			( false );
	this->setdelwep			( false );
	this->setwepcooldown	( false );
	this->setpickitem		( false );
	this->setcommand		( false );
	this->setcollision		( false );
	this->setsplashscreen	( false );
	this->setrestart		( false );
}

EventHandler::~EventHandler()
{

}

void EventHandler::update( float frametime )
{
	if( this->getdeath() == true )
	{
		this->setdeath( false );
	}

	if( this->getrespawn() == true )
	{
		this->setrespawn( false );
	}

	if( this->getgamestart() == true )
	{
		this->setgamestart( false );
	}

	if( this->getgameover() == true )
	{
		this->setgameover( false );
	}

	if( this->getswitchwep() == true )
	{
		this->setswitchwep( false );
	}

	if( this->getshot() == true )
	{
		this->setshot( false );
	}

	if( this->getfrag() == true )
	{
		this->setfrag( false );
	}

	if( this->getwall() == true )
	{
		this->setwall( false );
	}

	if( this->getquit() == true )
	{
		this->setquit( false );
	}

	if( this->getdelwep() == true )
	{
		this->setdelwep( false );
	}

	if( this->getwepcooldown() == true )
	{
		this->setwepcooldown( false );
	}
	//
	if( this->getpickitem() == true )
	{
		this->setpickitem( false );
	}

	if( this->getcollision() == true )
	{
		this->setcollision( false );
	}

	if( this->getsplashscreen() == true )
	{
		this->setsplashscreen( false );
	}

	if( this->getrestart() == true )
	{
		this->setrestart( false );
	}
}

void EventHandler::handleEvents()
{

}

void EventHandler::render( sf::RenderWindow *rw )
{

}

bool EventHandler::onDeath()
{
	if( getdeath() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onRespawn()
{
	if( getrespawn() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onGameStart()
{
	if( getgamestart() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onGameOver()
{
	if( getgameover() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onSwitchWeapon()
{
	if( getswitchwep() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onShot()
{
	if( getshot() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onFrag()
{
	if( getfrag() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onWall()
{
	if( getwall() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onQuit()
{
	if( getquit() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onDelWeapon()
{
	if( getdelwep() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onWeaponCooldown()
{
	if( getwepcooldown() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onPickItem()
{
	if( getpickitem() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onCommand()
{
	if( getcommand() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onCollision()
{
	if( getcollision() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onSplashScreen()
{
	if( getsplashscreen() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}

bool EventHandler::onRestart()
{
	if( getrestart() == true )
	{
		return true;
	}

	else

	{
		return false;
	}
}
