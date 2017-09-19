#pragma once

#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include "project_libraries.h"

#define TRUE 1
#define FALSE 0

#define DIMENSION_X 41 //MINIMALNIE 40
#define DIMENSION_Y 26
#define SPACE_BETWEEN_OBSTACLE 4
#define Y_BUFFER_DIMENSION 1
#define BACKGROUND_TEXTURE_CHAR 'Û' // 'Û' '°' - dwie opcje grafiki he he
#define LAST_COLUMN ( DIMENSION_X - 1 ) // indeks ostatniej kolumny w tablicy
#define LAST_VISIBLE_ROW ( DIMENSION_Y - 1 )
#define INVISIBLE_ROW ( DIMENSION_Y + Y_BUFFER_DIMENSION - 1 )
#define ESC_KEY 27
#define SPACE_KEY 32
#define FIRST_ARROWS_KEY 224 //pierwszy znak pojawiajacy sie po naciœniêciu dowolnej strzalki
#define DOWN_ARROW_KEY 80
#define LEFT_ARROW_KEY 75
#define RIGHT_ARROW_KEY 77
#define PLAYER_TEXTURE_CHAR ' ' //'Û'
#define OBSTACLE_TEXTURE_CHAR '1' //MUSI BYC CYFR¥ W POSTACI ZNAKU np. '0', '1', itd. ABY DZIA£A£A FUNKCJA isdigit. U¿ycie tego jest spowodowane tylko wymogiem u¿ycia tej funkcji w programie
#define STARTING_UP_STEP_TIME 500 //POCZ¥TKOWA SZYBKOŒC GRY. IM MNIEJ TYM SZYBCIEJ. wartoœæ czasu w milisekundach po której przeszkody przesuwaj¹ siê w górê
#define MIN_UP_STEP_TIME 100 // NAJWIEKSZA MOZLIWA SZYBKOSC GRY. najkrótsza wartoœæ czasu w milisekundach po której przeszkody przesuwaj¹ siê w górê
#define CURSOR_RESET_DEFAULT_POSITION 0
#define TIME_RESET_CONSTANT 1000 //wartoœæ co jak¹ zeruje siê licznik czasu. Dla sekund to 60, dla milisekund 1000
#define PLAYER_STARTING_POSITION_Y 15 
#define PLAYER_STARTING_LEFT_POSITION_X 10
#define PLAYER_STARTING_RIGHT_POSITION_X 12
#define PLAYER_LENGTH ( PLAYER_STARTING_RIGHT_POSITION_X - PLAYER_STARTING_LEFT_POSITION_X + 1 ) //+1 poniewa¿ zmienne oznaczaj¹ pozycjê pocz¹tku bloku gracza i pozycje koñca, jeœli pocz¹tek = koniec to znaczy, ¿e blok zajmuje jedno miejsce. Analogicznie left = 1, right = 3 oczacza, ¿e blok jest na pozycjach 1 2 3, wiec ma dlugosc rowna 3 
#define MAX_ADDITIONAL_HOLE_SIZE 10 // wielkoœæ dziury w przeszkodzie jest losowana z przedzia³u 0 - (MAX_ADDITIONAL_HOLE_SIZE - 1) i dodawana do PLAYER_LENGTH, które jest minimaln¹ wielkoœci¹ dziury w przeszkodzie, aby da³o siê przez ni¹ przejœæ
#define INITIAL_INFORMATION_ROW1 7
#define INITIAL_INFORMATION_ROW2 8
#define INITIAL_INFORMATION_ROW3 9
#define INITIAL_INFORMATION_ROW4 10
#define SCORES_FILENAME "falling_scores.txt"
#define FALLING_MINIGAME_IMG_PATH "media/falling_minigame.png"
// move it to snake header later
#define SNAKE_MINIGAME_IMG_PATH "media/snake_minigame.png"
#define PLAY_FALLING_MINIGAME_B_TLCX  ACTIVE_WINDOW_TLCX + GO_BACK_B_WIDTH
#define PLAY_FALLING_MINIGAME_B_TLCY ACTIVE_WINDOW_TLCY
#define PLAY_FALLING_MINIGAME_B_WIDTH 120
#define PLAY_FALLING_MINIGAME_B_HEIGHT 60
#define PLAY_SNAKE_MINIGAME_B_TLCX ACTIVE_WINDOW_TLCX + 440
#define PLAY_SNAKE_MINIGAME_B_TLCY PLAY_FALLING_MINIGAME_B_TLCY
#define PLAY_SNAKE_MINIGAME_B_WIDTH 120
#define PLAY_SNAKE_MINIGAME_B_HEIGHT 60

void create_board(char row[][DIMENSION_X], int * playerPositionY, int * playerLeftPositionX, int * playerRightPositionX);
void show_board(char row[][DIMENSION_X], int score);
void generate_row(char row[][DIMENSION_X]);
int play_falling_minigame(char animalName[]);