/*
* Filename: Main.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "main" class 
* Purpose 2: It's the heart of game, it executes engine class ( main )
*/


#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <fstream>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Config.hpp>
#include <SFML\Network.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "Engine.hpp"
#include "Commandhandler.hpp"

/* START GAME */
int main()
{
	Engine engine;
	engine.start();
}