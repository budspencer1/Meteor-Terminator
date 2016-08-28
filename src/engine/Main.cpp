/*
* Filename: Main.cpp
* Date: 2016 
* Author: Sebastian <3
* Purpose: This file executes "main" class 
* NOTE: It's the heart of game, it executes engine class ( main )
*/
#pragma once

#include "Engine.hpp"
#include "Main.hpp"

#include "Settings.inc"
#include "Version.inc"

/* specify used namespaces */
using namespace sf;
using namespace std;

/* START SPLASH SCREEN AND THEN GAME */ 

int main()
{
	//FreeConsole(); /* remove stupid console window ...	FOR DEVELOPERS::: comment that function if you wanna see comsole for some debug outputs */

	Engine engine;
	engine.start();

	return INIT_SUCCESS;
}