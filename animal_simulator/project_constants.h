#pragma once
//macros used in project (names abbreviations on the end)
//dimensions of main application structure's windows and buttons are responsive to dimentions of some main parts pointed by /*M*/

/*GENERAL*/
#define TRUE 1
#define FALSE 0
/*MAIN WINDOW*/
/*M*/#define MAIN_WINDOW_WIDTH 960
/*M*/#define MAIN_WINDOW_HEIGHT 540
/*STATIC WINDOWS*/ // static means here that type of content in the window doesn't change, however the items in this content can change (e.g. active events window is always in the right top corner, but single events in this window can change)
/*M*/#define ACTIVE_EVENTS_WINDOW_WIDTH 400
/*M*/#define ACTIVE_EVENTS_WINDOW_HEIGHT 140
#define ACTIVE_EVENTS_WINDOW_TLCX 0
#define ACTIVE_EVENTS_WINDOW_TLCY 0
#define ACTIVE_EVENTS_WINDOW_RGBA_COLOR 26, 188, 156, 255
/*M*/#define NEEDS_BARS_WINDOW_WIDTH 480
#define NEEDS_BARS_WINDOW_HEIGHT ACTIVE_EVENTS_WINDOW_HEIGHT
#define NEEDS_BARS_WINDOW_TLCX ACTIVE_EVENTS_WINDOW_WIDTH
#define NEEDS_BARS_WINDOW_TLCY 0
#define NEEDS_BARS_WINDOW_RGBA_COLOR 243, 156, 18, 255
#define TEXT_EVENTS_WINDOW_WIDTH MAIN_WINDOW_WIDTH
#define TEXT_EVENTS_WINDOW_HEIGHT (MAIN_WINDOW_HEIGHT - ACTIVE_EVENTS_WINDOW_HEIGHT - ACTIVE_WINDOW_HEIGHT)
#define TEXT_EVENTS_WINDOW_TLCX 0
#define TEXT_EVENTS_WINDOW_TLCY (MAIN_WINDOW_HEIGHT - TEXT_EVENTS_WINDOW_HEIGHT)
#define TEXT_EVENTS_WINDOW_RGBA_COLOR 192, 57, 43, 255
/*CHARACTER / SHOP / GAME / FOOD / DRINK WINDOW*/
/*M*/#define	ACTIVE_WINDOW_WIDTH 800
/*M*/#define ACTIVE_WINDOW_HEIGHT 280
#define ACTIVE_WINDOW_TLCX (MAIN_WINDOW_WIDTH - ACTIVE_WINDOW_WIDTH)
#define ACTIVE_WINDOW_TLCY ACTIVE_EVENTS_WINDOW_HEIGHT
/*STATIC BUTTONS*/
#define SHOP_B_WIDTH (MAIN_WINDOW_WIDTH - ACTIVE_WINDOW_WIDTH)
#define SHOP_B_HEIGHT (ACTIVE_WINDOW_HEIGHT/2)
#define SHOP_B_TLCX 0
#define SHOP_B_TLCY ACTIVE_WINDOW_TLCY
#define SHOP_B_LEFT_TEXT_PADDING 50
#define SHOP_B_TOP_TEXT_PADDING 50
#define SHOP_B_RGBA_COLOR_INACTIVE 236, 240, 241, 255
#define SHOP_B_RGBA_COLOR_HIGHLIGHTED 149, 165, 166, 255
#define SHOP_B_RGBA_COLOR_ACTIVE 52, 73, 94, 255
#define GAMES_B_WIDTH SHOP_B_WIDTH
#define GAMES_B_HEIGHT SHOP_B_HEIGHT
#define GAMES_B_TLCX 0
#define GAMES_B_TLCY (SHOP_B_TLCY + SHOP_B_HEIGHT)
#define GAMES_B_LEFT_TEXT_PADDING 40
#define GAMES_B_TOP_TEXT_PADDING 50
#define GAMES_B_RGBA_COLOR_INACTIVE 236, 240, 241, 255
#define GAMES_B_RGBA_COLOR_HIGHLIGHTED 149, 165, 166, 255
#define GAMES_B_RGBA_COLOR_ACTIVE 52, 73, 94, 255
#define EXIT_B_WIDTH (MAIN_WINDOW_WIDTH - ACTIVE_EVENTS_WINDOW_WIDTH - NEEDS_BARS_WINDOW_WIDTH)
#define EXIT_B_HEIGHT (ACTIVE_EVENTS_WINDOW_HEIGHT/2)
#define EXIT_B_TLCX (MAIN_WINDOW_WIDTH - EXIT_B_WIDTH)
#define EXIT_B_TLCY 0
#define EXIT_B_LEFT_TEXT_PADDING 15
#define EXIT_B_TOP_TEXT_PADDING 20
#define EXIT_B_RGBA_COLOR_INACTIVE 236, 240, 241, 255
#define EXIT_B_RGBA_COLOR_HIGHLIGHTED 149, 165, 166, 255
#define EXIT_B_RGBA_COLOR_ACTIVE 52, 73, 94, 255
#define SAVE_B_WIDTH EXIT_B_WIDTH
#define SAVE_B_HEIGHT (ACTIVE_EVENTS_WINDOW_HEIGHT/2)
#define SAVE_B_TLCX EXIT_B_TLCX
#define SAVE_B_TLCY EXIT_B_HEIGHT
#define SAVE_B_LEFT_TEXT_PADDING 5
#define SAVE_B_TOP_TEXT_PADDING 20
#define SAVE_B_RGBA_COLOR_INACTIVE 236, 240, 241, 255
#define SAVE_B_RGBA_COLOR_HIGHLIGHTED 149, 165, 166, 255
#define SAVE_B_RGBA_COLOR_ACTIVE 52, 73, 94, 255
/*NEEDS BARS*/
#define NEED_BAR_WIDTH 200
#define NEED_BAR_HEIGHT 20
#define NEED_BAR_TEXT_SPACE_HEIGHT 20
#define NEED_BARS_PADDING_FROM_TOP 40 // ~ height of space for "needs bars" text
#define NEED_BAR_BOTTOM_PADDING 10 // bottom padding of every bar 
#define NEED_BAR_SIDE_PADDING 20 // left and right padding of every bar 
#define NEED_BAR_BORDER_RGBA_COLOR 0, 0, 0, 255
#define NEED_BAR_RGBA_COLOR_EMPTY 255, 255, 255, 255
#define NEED_BAR_RGBA_COLOR_FILLING 205, 220, 57, 255
#define HUNGER_BAR_TEXT_TLCX (NEEDS_BARS_WINDOW_TLCX + NEED_BAR_SIDE_PADDING)
#define HUNGER_BAR_TEXT_TLCY (NEEDS_BARS_WINDOW_TLCY + NEED_BARS_PADDING_FROM_TOP)
#define THIRST_BAR_TEXT_TLCX HUNGER_BAR_TEXT_TLCX
#define THIRST_BAR_TEXT_TLCY (HUNGER_BAR_TEXT_TLCY + NEED_BAR_HEIGHT + NEED_BAR_BOTTOM_PADDING + NEED_BAR_TEXT_SPACE_HEIGHT)
#define ENERGY_BAR_TEXT_TLCX (HUNGER_BAR_TEXT_TLCX + NEED_BAR_WIDTH + (2*NEED_BAR_SIDE_PADDING))
#define ENERGY_BAR_TEXT_TLCY HUNGER_BAR_TEXT_TLCY
#define FUN_BAR_TEXT_TLCX ENERGY_BAR_TEXT_TLCX
#define FUN_BAR_TEXT_TLCY THIRST_BAR_TEXT_TLCY
#define MAX_BAR_VALUES_TEXT_SIZE 12 // xxxxx/yyyyy\n

//#define SLEEP_B_WIDTH 
//#define SLEEP_B_HEIGHT 
//#define FOOD_B_WIDTH 
//#define FOOD_B_HEIGHT 
//#define DRINKS_B_WIDTH 
//#define DRINKS_B_HEIGHT 
//#define TOY_B_WIDTH 
//#define TOY_B_HEIGHT 

/*
	names abbreviations:
b - button
TLC - top left corner


*/