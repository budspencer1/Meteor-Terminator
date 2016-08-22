/* 
* File Name: Sounds.cpp
* Author: Sebastian <3
* Date: 2016
* Purpose: HANDLE RAMPAGE SOUND TO DONT OVERFLOW PLAYER
*/


#include "Sounds.hpp"
#include "Settings.inc"



Sounds::Sounds( Player *player )
{
	pRampage = player;

	RampageLabelClock	=		new sf::Clock;
	RampageLabelClock->restart();

	RampageSound	=			new sf::Sound;

	blood_			=			new sf::SoundBuffer;
	killingspree	=			new sf::SoundBuffer;			
	rampage 		=			new sf::SoundBuffer;
	dominating		=			new sf::SoundBuffer;
	unstoppable		=			new sf::SoundBuffer;
	ownage			=			new sf::SoundBuffer;
	godlike			=			new sf::SoundBuffer;


	blood_->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/FirstBlood.wav" ) );
	killingspree->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/KillingSpree.wav" ) );
	rampage->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/Rampage.wav" ) );	
	dominating->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/Dominating.wav" ) );
	unstoppable->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/Unstoppable.wav" ) );	
	ownage->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/Ownage.wav" ) );		
	godlike->loadFromFile( std::string( "media/packages/content/sounds/RampageMode/Godlike.wav" ) );		


	font			=			new sf::Font;
	font->loadFromFile( std::string( "media/packages/content/fonts/Cocogoose.otf" ) );

	label.setFont( *font );
	label.setCharacterSize( 60 );
	label.setColor( sf::Color::Yellow );
	label.setPosition( sf::Vector2f( RES_X - 900 , RES_Y - ( RES_Y - 20 ) ) );

	enableSounds	= true;
	numSounds		= 7;

	play_sound		= false;

	blood			= 1;
	first			= 5;
	second			= 15;
	third			= 25;
	fourth			= 35;
	fifth			= 45;
	sixth			= 55;

	value			= NULL;

	canSet2			= true;

	soundPaused		= false;
	soundPlayed		= false;
	soundStopped	= false;
	visible			= false;
}


Sounds::~Sounds()
{
	delete blood_;
	delete killingspree;
	delete rampage;
	delete dominating;
	delete unstoppable;
	delete ownage;
	delete godlike;

	delete RampageSound;
	delete font;
	delete RampageLabelClock;


	blood_		   = nullptr;
	killingspree   = nullptr;
	rampage		   = nullptr;
	dominating	   = nullptr;
	unstoppable	   = nullptr;
	ownage		   = nullptr;
	godlike		   = nullptr;

	RampageSound			= nullptr;
	font					= nullptr;
	RampageLabelClock		= nullptr;
}

void Sounds::update( float frametime )
{
	if( pRampage->getIsRampageMode() )
	{
		if( pRampage->getRampageFrags() == blood && canSet2 == true )
		{
			play_sound = true;
			value = blood;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == first && canSet2 == true )
		{
			play_sound = true;
			value = first;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == second && canSet2 == true )
		{
			play_sound = true;
			value = second;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == third && canSet2 == true )
		{
			play_sound = true;
			value = third;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == fourth && canSet2 == true )
		{
			play_sound = true;
			value = fourth;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == fifth && canSet2 == true )
		{
			play_sound = true;
			value = fifth;
			canSet2 = false;
		}

		else if( pRampage->getRampageFrags() == sixth && canSet2 == true )
		{
			play_sound = true;
			value = sixth;
			canSet2 = false;
		}

		else

		{
			if( pRampage->getRampageFrags() != blood && pRampage->getRampageFrags() != first && pRampage->getRampageFrags() != second && pRampage->getRampageFrags() != third && pRampage->getRampageFrags() != fourth && pRampage->getRampageFrags() != fifth && pRampage->getRampageFrags() != sixth )
			{
				canSet2 = true;
			}
		}

		this->play();
		this->pause();
		this->stop();

		if( visible )
		{
			if( RampageLabelClock->getElapsedTime().asSeconds() > 1 )
			{
				visible = false;
				RampageLabelClock->restart();
			}
		}
	}
}

void Sounds::handleEvents()
{

}

void Sounds::render( sf::RenderWindow *rw )
{
	if( pRampage->getIsRampageMode() )
	{
		if(  pRampage->getRampageFrags() == blood )
		{ 
			label.setString( std::string( "First Kill!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == first )
		{
			label.setString( std::string( "Killing Spree!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == second )
		{ 
			label.setString( std::string( "Rampage!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == third )
		{
			label.setString( std::string( "Dominating!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == fourth )
		{
			label.setString( std::string( "Unstoppable!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == fifth )
		{ 
			label.setString( std::string( "Ownage!" ) );
			visible = true;
		}

		else if(  pRampage->getRampageFrags() == sixth )
		{
			label.setString( std::string( "Godlike!" ) );
			visible = true;
		}

		if( visible )
		{
			rw->draw( label );
		}
	}
}

void Sounds::play()
{
	if(  pRampage->getRampageFrags() == blood && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *blood_ );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == first && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *killingspree );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == second && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *rampage );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == third && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *dominating );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == fourth && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *unstoppable );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == fifth && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *ownage );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}

	else if( pRampage->getRampageFrags() == sixth && play_sound == true )
	{
		soundPlayed = true;
		RampageSound->setBuffer( *godlike );
		RampageSound->play();
		play_sound = false;
		soundPlayed = false;
	}
}

void Sounds::pause()
{
	if( this->soundPaused == true )
	{
		RampageSound->pause();
	}
}

void Sounds::stop()
{
	if( this->soundStopped == true )
	{
		RampageSound->stop();
	}
}



