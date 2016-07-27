/* 
* File Name: Commandhandler.cpp
* Date: 2016
* Author: Sebastian <3
* Purpose: Handle all commands for console subsystem
*/


#include "Commandhandler.hpp"



CommandHandler::CommandHandler()
{
	pOverflowCheckClock			= new sf::Clock();
	pOverflowCheckClock->restart();

	pCommandResetClock			= new sf::Clock();
	pCommandResetClock->restart();

	this->setIsActivated( true );
	this->setCommands( 0 );
	this->setIsMuted( false );
	this->setIsOutOfAmmo( false );
	this->setIsPaused( false );
}

CommandHandler::~CommandHandler()
{
	delete pOverflowCheckClock;
	delete pCommandResetClock;

	pOverflowCheckClock = nullptr;
	pCommandResetClock  = nullptr;
}

void CommandHandler::activate()
{
	if( this->getIsActivated() == true )
	{
		std::cout << "ERROR: Command System is already activated." << std::endl;
	}

	else

	{
		this->setIsActivated( true );
		std::cout << "INFO: Command System is activated now." << std::endl;
	}

	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::deactivate()
{
	if( this->getIsActivated() == false )
	{
		std::cout << "ERROR: Command System is already deactivated." << std::endl;
	}

	else

	{
		this->setIsActivated( false );
		std::cout << "INFO: Command System is deactivated now." << std::endl;
	}

	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::update( float frametime )
{
	if( pOverflowCheckClock->getElapsedTime().asSeconds() == 2 )
	{
		if( this->getCommands() == 5 || this->getCommands() > 5 )
		{
			this->setIsMuted( true );
			this->setCommands( 0 );
			std::cout << "PROTECT: You've been muted, because you tried to do Overflow." << std::endl;
			pOverflowCheckClock->restart();
		}

		else

		{
			this->setCommands( 0 );
		}
	}
}

void CommandHandler::handleEvents()
{

}

void CommandHandler::render( sf::RenderWindow *rw )
{

}

/* //////////////////////////////////////////////////////////////// */

void CommandHandler::help()
{
	std::cout << COMMAND_LIST << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::about()
{
	std::cout << "Game Name: " TERM_NAME "\nGame Version: " TERM_HISTORY " " TERM_VERSION "\nDeveloper: " TERM_DEVELOPER "\nUpdate Game: " TERM_DL_UPDATE_URL "" << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::info()
{
	std::cout << INFO_MSG << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::enable_vsync( sf::RenderWindow *rw )
{
	rw->setVerticalSyncEnabled( true );
	std::cout << "INFO: Vertical Syncronisation is enabled now." << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::disable_vsync( sf::RenderWindow *rw )
{
	rw->setVerticalSyncEnabled( false );
	std::cout << "INFO: Vertical Syncronisation is disabled now." << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::enable_mousecurser( sf::RenderWindow *rw )
{
	rw->setMouseCursorVisible( true );
	std::cout << "INFO: Mouse Curser is visible now." << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::disable_mousecurser( sf::RenderWindow *rw )
{
	rw->setMouseCursorVisible( false );
	std::cout << "INFO: Mouse Curser is invisible now." << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::suicide()
{
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::restart()
{
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::respawn()
{
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::outofammo( Weapon *weapon )
{
	pWeapon->setAmmo( 0 );
	std::cout << "INFO: No Ammo left. (Out of Ammo.)" << std::endl;
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::weapon1( Weapon *weapon )
{
	if( weapon->getWeapon() != 1 )
	{
		weapon->setWeapon( 1 );
		std::cout << "INFO: Weapon has changed to '1'(Cannon)." << std::endl;
		this->setCommands( this->getCommands() + 1 );
	}
}

void CommandHandler::weapon2( Weapon *weapon )
{
	if( weapon->getWeapon() != 2 )
	{
		weapon->setWeapon( 2 );
		std::cout << "INFO: Weapon has changed to '2'(Minigun)." << std::endl;
		this->setCommands( this->getCommands() + 1 );
	}
}

void CommandHandler::pause()
{

}

void CommandHandler::menu()
{

}

void CommandHandler::stats()
{
	this->setCommands( this->getCommands() + 1 );
}

void CommandHandler::mute()
{
	this->setIsMuted( true );
	std::cout << "You've been muted by game, it thinks, it's better for everyone." << std::endl;
}




