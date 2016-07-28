/* 
* Meteor Terminator Control & Version System
* Author: Sebastian <3
* Date: 2016
* Purpose: Manage Version & Control of program
* NOTE: CONTAINS SOME DEFAULT SETTINGS OF GAME
*/

#include <time.h>

/* Official name of Game */

#ifndef TERM_NAME 
#define TERM_NAME "Meteor Terminator"
#endif 

/* Name of developer listed in list */

#ifndef TERM_DEVELOPER
#define TERM_DEVELOPER "Sebastian <3" 
#endif

/* Version Overlay (Alpha, Beta, Remake, ...) */

#ifndef TERM_HISTORY 
#define TERM_HISTORY "Alpha"
#endif 

/* Game Version (will be changed on release) */
#ifndef TERM_VERSION
#define TERM_VERSION "1.1.5_06"
#endif

/* Url to download or update game */

#ifndef TERM_DL_UPDATE_URL 
#define TERM_DL_UPDATE_URL "https://github.com/budspencer1/Meteor-Terminator"
#endif

#ifndef COMPILE_TIME
#define COMPILE_TIME __TIME__
#endif

#ifndef COMPILE_DATE 
#define COMPILE_DATE __DATE__
#endif

#ifndef TERM_ARCHITECTURE 
#define TERM_ARCHITECTURE "x86 (32 Bit)"
#endif

#ifndef SFML_ARCHITECTURE
#define SFML_ARCHITECTURE "x86 (32 Bit)"
#endif







