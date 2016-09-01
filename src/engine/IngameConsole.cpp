/*
* FileName: IngameConsole.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: define functions of ingame console
*/


#include "IngameConsole.hpp"



std::string input;
std::string output;

Console::Console()
{
	font			= new sf::Font;
	TextEvent		= new sf::Event;

	font->loadFromFile( std::string( "media/packages/content/fonts/Cocogoose.otf" ) );

	inputT.setFont( *font );
	inputT.setCharacterSize( 30 );
	inputT.setColor( sf::Color::Blue );
	inputT.setPosition( sf::Vector2f( RES_X - 1300 , RES_Y - 40 ) );
	inputT.setString( std::string( input ) );
}


Console::~Console()
{
	delete TextEvent;
	delete font;

	font		= nullptr;
	TextEvent	= nullptr;
}


void Console::updateConsole( float frametime , CommandHandler *cmdhan )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::T ) )
	{
		if( !isOpen )
		{
			isOpen = true;
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Escape ) )
	{
		if( isOpen )
		{
			isOpen = false;
		}
	}
}


void Console::handleConsole()
{
	if( TextEvent->type == sf::Event::TextEntered )
	{
		if( TextEvent->text.unicode == '\b' )
		{
			if( input != "" )
			{
				input.erase( input.size() - 1 , 1 );
			}
		}

		else
		{
			if( TextEvent->text.unicode < 128 )
			{
				if( ( input.size() < 120 || input.size() == 120 ) )
				{
					if( isOpen )
					{
						input += static_cast<char>( TextEvent->text.unicode );
					}
				}
			}
		}
	}

	inputT.setString( std::string( input ) );
}


void Console::renderConsole( sf::RenderWindow *rw )
{
	if( isOpen )
	{
		rw->draw( inputT );
		rw->draw( outputT );
	}
}

