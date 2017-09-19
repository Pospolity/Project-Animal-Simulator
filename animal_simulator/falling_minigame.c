#define _CRT_SECURE_NO_WARNINGS

#include "falling_minigame.h"

int play_falling_minigame(char animalName[])
{
	SYSTEMTIME st;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorReset;
	cursorReset.X = CURSOR_RESET_DEFAULT_POSITION;
	cursorReset.Y = CURSOR_RESET_DEFAULT_POSITION;

	srand(time(NULL));
	FILE *scoresFile;
	if ((scoresFile = fopen(SCORES_FILENAME, "a+")) == NULL) {
		printf("Nie mogê otworzyæ pliku %s do zapisu!\n", SCORES_FILENAME);
		exit(1);
	}

	static int thisGameHighScore = 0;

	unsigned char row[DIMENSION_Y + Y_BUFFER_DIMENSION][DIMENSION_X];
	int playerPositionY;
	int playerLeftPositionX;
	int playerRightPositionX;
	int verticalChange = FALSE;
	int horizontalChange = TRUE;
	int still_running;
	unsigned char key;
	int spaceBetweenObstaclesCounter;
	int score;
	int totalScore = 0;
	int expiredTime;
	unsigned int upStepTime; //szybkoœæ gry. Im mniej tym szybciej.
	GetLocalTime(&st);
	Uint32 startTime = 0;
	while (1) {
		system("cls");
		still_running = TRUE;
		score = 0;
		spaceBetweenObstaclesCounter = 0;
		upStepTime = STARTING_UP_STEP_TIME;
		create_board(row, &playerPositionY, &playerLeftPositionX, &playerRightPositionX);
		cursorReset.Y = playerPositionY;
		show_board(row, score);
		while (still_running) {
			if (horizontalChange) {
				SetConsoleCursorPosition(handle, cursorReset);
				puts(row[playerPositionY]);
				horizontalChange = 0;
			}
			else if (verticalChange) {
				cursorReset.Y = playerPositionY - 1;
				SetConsoleCursorPosition(handle, cursorReset);
				puts(row[playerPositionY - 1]);
				puts(row[playerPositionY]);
				verticalChange = 0;
				cursorReset.Y = playerPositionY;
			}
			expiredTime = SDL_GetTicks() - startTime;
			if (expiredTime >= upStepTime) {
				startTime = SDL_GetTicks();
				cursorReset.Y = CURSOR_RESET_DEFAULT_POSITION;
				SetConsoleCursorPosition(handle, cursorReset);
				if (spaceBetweenObstaclesCounter == SPACE_BETWEEN_OBSTACLE) {
					if (upStepTime > MIN_UP_STEP_TIME)
						upStepTime -= 5; // zwiekszenie szybkosci gry z kazda pojawiajaca sie przeszkoda
					generate_row(row);
					memmove(row, row + 1, sizeof(row) - sizeof(row[INVISIBLE_ROW]));
					score++;
					show_board(row, score);
					memset(row[INVISIBLE_ROW], BACKGROUND_TEXTURE_CHAR, DIMENSION_X);
					row[INVISIBLE_ROW][LAST_COLUMN] = '\0';
					playerPositionY--;
					cursorReset.Y = playerPositionY;
					spaceBetweenObstaclesCounter = 0;
				}
				else {
					memmove(row, row + 1, sizeof(row) - sizeof(row[INVISIBLE_ROW]));
					show_board(row, score);
					playerPositionY--;
					cursorReset.Y = playerPositionY;
					spaceBetweenObstaclesCounter++;
				}
				if (playerPositionY == 0)
					still_running = 0;
			}
			while (_kbhit()) {
				key = _getch();
				if (key == ESC_KEY) {
					still_running = 0;
					break;
				}
				else if (key == FIRST_ARROWS_KEY) { //niepo¿¹dane dzia³anie programu nast¹pi gdy u¿ytkownik naciœnie 'Ó', program zaczeka na dowolny klawisz, po czym go zignoruje i bêdzie kontynuowa³ dzia³anie
					key = _getch();
					if (key == LEFT_ARROW_KEY && !isdigit(row[playerPositionY][playerLeftPositionX - 1]) && playerLeftPositionX > 0) {
						memmove(row[playerPositionY] + playerLeftPositionX - 1, row[playerPositionY] + playerLeftPositionX, PLAYER_LENGTH);
						row[playerPositionY][playerRightPositionX] = BACKGROUND_TEXTURE_CHAR;
						playerLeftPositionX--;
						playerRightPositionX--;
						horizontalChange = 1;
					}
					if (key == RIGHT_ARROW_KEY && !isdigit(row[playerPositionY][playerRightPositionX + 1]) && playerRightPositionX < LAST_COLUMN - 1) {
						memmove(row[playerPositionY] + playerLeftPositionX + 1, row[playerPositionY] + playerLeftPositionX, PLAYER_LENGTH);
						row[playerPositionY][playerLeftPositionX] = BACKGROUND_TEXTURE_CHAR;
						playerLeftPositionX++;
						playerRightPositionX++;
						horizontalChange = 1;
					}
					if (key == DOWN_ARROW_KEY && !isdigit(row[playerPositionY + 1][playerLeftPositionX]) && !isdigit(row[playerPositionY + 1][playerRightPositionX]) && playerPositionY < LAST_VISIBLE_ROW) {
						memcpy(row[playerPositionY + 1] + playerLeftPositionX, row[playerPositionY] + playerLeftPositionX, PLAYER_LENGTH);
						for (int i = playerLeftPositionX; i <= playerRightPositionX; i++)
							row[playerPositionY][i] = BACKGROUND_TEXTURE_CHAR;
						playerPositionY++;
						verticalChange = 1;
					}
				}
			}
		}
		system("cls");
		GetLocalTime(&st);
		char text[100];
		sprintf(text, "wynik: %d data: %d.%d.%d %d:%d zwierzak: %s\n", score, st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, animalName);
		fputs(text, scoresFile);
		if (score > thisGameHighScore)
			thisGameHighScore = score;
		printf("Najlepszy wynik od wczytania lub utworzenia gry to: %d\n", thisGameHighScore);
		sprintf(text, "Twoj wynik to: %d\n", score);
		char text2[] = "Wcisnij spacje aby kontynuowac, lub esc, aby wyjsc z programu";
		strcat(text, text2);
		puts(text);
		key = _getch();
		while (key != SPACE_KEY && key != ESC_KEY)
			key = _getch();
		totalScore += score;
		if (key == ESC_KEY) {
			fclose(scoresFile);
			return totalScore;
		}
	}
}

void create_board(char row[][DIMENSION_X], int * playerPositionY, int * playerLeftPositionX, int * playerRightPositionX) //tworzenie planszy
{
	for (int i = 0; i < DIMENSION_Y + Y_BUFFER_DIMENSION; i++) {
		memset(row[i], BACKGROUND_TEXTURE_CHAR, DIMENSION_X);
		row[i][LAST_COLUMN] = '\0';
	}
	*playerPositionY = PLAYER_STARTING_POSITION_Y;
	*playerLeftPositionX = PLAYER_STARTING_LEFT_POSITION_X;
	*playerRightPositionX = PLAYER_STARTING_RIGHT_POSITION_X;
	for (int i = *playerLeftPositionX; i <= *playerRightPositionX; i++)
		row[*playerPositionY][i] = PLAYER_TEXTURE_CHAR;
	strcpy(row[INITIAL_INFORMATION_ROW1] + 1, "steruj strzalkami w dol i na boki"); row[INITIAL_INFORMATION_ROW1][34] = BACKGROUND_TEXTURE_CHAR; //NIE MODYFIKOWAC
	strcpy(row[INITIAL_INFORMATION_ROW2] + 3, "celuj w przerwy miedzy zerami"); row[INITIAL_INFORMATION_ROW2][32] = BACKGROUND_TEXTURE_CHAR; //NIE MODYFIKOWAC
	strcpy(row[INITIAL_INFORMATION_ROW3] + 5, "nie daj sie wypchnac poza plansze!"); row[INITIAL_INFORMATION_ROW3][39] = BACKGROUND_TEXTURE_CHAR; //NIE MODYFIKOWAC
	strcpy(row[INITIAL_INFORMATION_ROW4] + 7, "ESC przerywa gre"); row[INITIAL_INFORMATION_ROW4][23] = BACKGROUND_TEXTURE_CHAR; //NIE MODYFIKOWAC
}

void show_board(char row[][DIMENSION_X], int score)
{
	for (int i = 0; i < DIMENSION_Y; i++)
		puts(row[i]);
	printf("SCORE: %d", score);
}

void generate_row(char row[][DIMENSION_X])
{
	memset(row[INVISIBLE_ROW], OBSTACLE_TEXTURE_CHAR, DIMENSION_X);
	int holeSize = PLAYER_LENGTH + rand() % MAX_ADDITIONAL_HOLE_SIZE; // wielkoœæ dziury w przeszkodzie jest losowana z przedzia³u 0 - (MAX_ADDITIONAL_HOLE_SIZE - 1) i dodawana do PLAYER_LENGTH, które jest minimaln¹ wielkoœci¹ dziury w przeszkodzie, aby da³o siê przez ni¹ przejœæ
	int maxHoleLeftPosition = DIMENSION_X - holeSize;
	int holeLeftPositionIndex = rand() % maxHoleLeftPosition; //zakres od 0 do (maxHoleLeftPosition - 1) poniewa¿ jest to indeks w tablicy row
	memset(row[INVISIBLE_ROW] + holeLeftPositionIndex, BACKGROUND_TEXTURE_CHAR, holeSize);
	row[INVISIBLE_ROW][LAST_COLUMN] = '\0';
}
