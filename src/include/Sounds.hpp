/*
* File Name: Sounds.hpp
* Author: Sebastian <3
* Date: 2016 
* Purpose: Custom Sounds Handler for Rampage Mode
* -----> that the player class dont overflow any time
*/


#ifndef SOUNDS_HPP
#define SOUNDS_HPP


#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "Player.hpp"


class Sounds  
{


public:

	Sounds( Player *player );
	~Sounds();

	void update( float frametime );
	void handleEvents();
	void render( sf::RenderWindow *rw );

	virtual void play();
	virtual void stop();
	virtual void pause();


private:

	Player							*pRampage;
	
	sf::SoundBuffer					*blood_;
	sf::SoundBuffer					*killingspree;
	sf::SoundBuffer					*rampage;
	sf::SoundBuffer					*dominating;
	sf::SoundBuffer					*unstoppable;
	sf::SoundBuffer					*ownage;
	sf::SoundBuffer					*godlike;

	sf::Clock						*RampageLabelClock;
	sf::Sound						*RampageSound;



	bool							enableSounds;
	unsigned int					numSounds;

	bool							play_sound;

	bool							soundPlayed;
	bool							soundPaused;
	bool							soundStopped;

	bool							canSet2;
	bool							visible;

	unsigned int					blood;
	unsigned int					first;
	unsigned int					second;
	unsigned int					third;
	unsigned int					fourth;
	unsigned int					fifth;
	unsigned int					sixth;

	unsigned int					value;

	/*
	* I know, that the following label isn't a sound but i need to declare it here 
	*/

	sf::Font						*font;
	sf::Text						label;


};

#endif