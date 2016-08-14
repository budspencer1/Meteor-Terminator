/* 
* Meteor Terminator Control & Version System
* Author: Sebastian <3
* Date: 2016
* Purpose: Manage Version & Control of program
* NOTE: CONTAINS SOME DEFAULT SETTINGS OF GAME
* NOTE: Will be changed in new commit/release
* INFO: Scheme: TERM_NAME " - Version: " TERM_DEVAGE
*/

#include <time.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Official name of Game */

#ifndef TERM_NAME 
#define TERM_NAME "Meteor Terminator"
#endif 

/* Name of developer listed in list */

#ifndef TERM_DEVELOPER
#define TERM_DEVELOPER "Sebastian <3" 
#endif

/* Version History (Alpha, Beta, Remake, Final, ...) */

#ifndef TERM_DEV_AGE 
#define TERM_DEV_AGE "Beta"
#endif 

/* Game Version (will be changed on release) */
#ifndef TERM_VERSION
#define TERM_VERSION "1.0.8_05"
#endif

/* Url to download or update game */

#ifndef TERM_DL_UPDATE_URL 
#define TERM_DL_UPDATE_URL "https://github.com/budspencer1/Meteor-Terminator"
#endif

#ifndef COMPILE_TIME
#define COMPILE_TIME __TIME__  /* time */
#endif

#ifndef COMPILE_DATE 
#define COMPILE_DATE __DATE__	/* date */
#endif

#ifndef TERM_REVISION
#define TERM_REVISION "Rev 1_03" /* build revision */
#endif






