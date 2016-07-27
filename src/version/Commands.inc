/*
* Console Command System 
* Author: Sebastian <3
* Date: 2016
* Purpose: define all executable commands
*/


/* define command handler */

#ifndef COMMANDS_ENGINE 
#define COMMANDS_ENGINE

#define COMMAND_NOT_DEFINED "Sorry, but this command wasn't found. Do #help to display commands list" 
#define INTERNAL_ERROR "Internal Error: Please check your typed parameters and retry."
#define ____OVERFLOW "OVERFLOW!!" 
#define COMMAND_LIST "Command List: help, about, info, arch, enable_vsync, disable_vsync, mousecurser, quit, suicide, restart, respawn, outofammo, delweapon, weapon1, weapon2, pause, menu, stats"
#define INFO_MSG "This game is written in C++ with additions from C and Assembler\nBased on SFML 2.1 (http://www.sfml-dev.org/)" 

/* console client commands */

#define HELP 
#define ABOUT 
#define INFO 
#define ENABLE_VSYNC 
#define DISABLE_VSYNC
#define ENABLE_MOUSE_CURSER
#define DISABLE_MOUSE_CURSER
#define QUIT
#define SUICIDE
#define	RESTART
#define RESPAWN
#define OUTOFAMMO
#define DELWEAPON
#define WEAPON1
#define WEAPON2
#define PAUSE
#define MENU
#define STATS
#define MUTE

#endif