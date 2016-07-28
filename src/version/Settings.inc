/* 
* Main Settings System 
* For weapon, player, framework, ...
* Author: Sebastian <3
* Date: 2016 
* Purpose: manage settings for objects + change them
*/


#include <time.h>


#ifndef PLAYER_X_POS 
#define PLAYER_X_POS 700 
#endif

#ifndef PLAYER_Y_POS
#define PLAYER_Y_POS 770 
#endif 

#ifndef SHIELD 
#define SHIELD 255
#endif

#ifndef LIFE
#define LIFE 255
#endif

#ifndef LIFES
#define LIFES 4
#endif

#ifndef AMMO
#define AMMO 700 
#endif

#ifndef COOLDOWN_WEP_1 
#define COOLDOWN_WEP_1 0.4
#endif

#ifndef COOLDOWN_WEP_2
#define COOLDOWN_WEP_2 0.05
#endif

#ifndef WAITTIME_IN_SEC
#define WAITTIME_IN_SEC 5
#endif

#ifndef DEFAULT_WEAPON
#define DEFAULT_WEAPON 1 /* Cannon */
#endif

#ifndef COMMAND_OVERFLOW_TIME
#define COMMAND_OVERFLOW_TIME 1
#endif

#ifndef COUNTDOWN_TIME_IN_MIN
#define COUNTDOWN_TIME_IN_MIN 5
#endif

/* ///////////////////////////////////////////////////////// */
/* Some important system settings */

/* resulution (x) in pixel */
#ifndef RES_X 
#define RES_X 1400 
#endif

/* resulution (y) in pixel */
#ifndef RES_Y 
#define RES_Y 900
#endif

/* change number of color bits */
#ifndef WINDOW_BITS 
#define WINDOW_BITS 32 
#endif 

/* set mouse curser visible or invisibe */
#ifndef MOUSE_CURSER_VISIBLE 
#define MOUSE_CURSER_VISIBLE false
#endif

/* enable/disable vsync */
#ifndef VERTICAL_SYNC_ENABLED
#define VERTICAL_SYNC_ENABLED true
#endif

/* enable or disable command system in console */
#ifndef ENABLE_COMMAND_SYSTEM
#define ENABLE_COMMAND_SYSTEM false
#endif

/* enable logging to disk */
#ifndef ENABLE_LOGGING
#define ENABLE_LOGGING true
#endif

/* ///////////////////////////////////////////////////////// */

/* Log informations */

#ifndef INIT
#define INIT "initializing"
#endif 

#ifndef ENGINE 
#define ENGINE "engine"
#endif

#ifndef CLOCK
#define CLOCK "clock" 
#endif

#ifndef MAINLOOP
#define MAINLOOP "mainloop"
#endif

#ifndef COMMAND_SYSTEM
#define COMMAND_SYSTEM "commandsystem" 
#endif

#ifndef VIDEOMODE 
#define VIDEOMODE "1400 x 900 (32 Bits)" 
#endif

#ifndef VIDEO_RENDERWINDOW
#define VIDEO_RENDERWINDOW "video: renderwindow: mode:" 
#endif

#ifndef RES_X_LOG
#define RES_X_LOG "1400"
#endif

#ifndef RES_Y_LOG 
#define RES_Y_LOG "900"
#endif

#ifndef WINDOW_BITS_LOG 
#define WINDOW_BITS_LOG "32"
#endif

/* ///////////////////////////////////////////////////////// */


