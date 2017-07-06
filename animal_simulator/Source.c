#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"

struct texture 
{
	SDL_Texture* texture;
	int tWidth;
	int tHeight;
};

int load_textures(void);
void free_textures(void);
void load_static_windows(void);
void load_static_buttons(void);

int load_textures()
{
	int success = TRUE;

	//---here we will be loading textures---

	return success;
}

void free_textures()
{
	;//---here we will need to free loaded textures when we will have any---
}

void load_static_windows(void) 
{
	;// load active events window

	//
}

void load_static_buttons(void)
{
	;//
	//
}

int main(int argc, char* args[])
{
	gameWindow = NULL;
	renderer = NULL;

	int success = TRUE;
	if (!SDL_initialize()) {
		success = FALSE;
		printf("Failed to initialize!\n");
	}
	if (success)
		if (!load_textures()) {
			success = FALSE;
			printf("Failed to load textures!\n");
		}
	if (success) {
		int quit = FALSE;
		SDL_Event e; //Event handler
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) { //Handling events on queue
				if (e.type == SDL_QUIT) //User requests quit by clicking the standard windows' close button
					quit = TRUE;
			}

			//Clearing the screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			load_static_windows();
			load_static_buttons();

			//Updating the screen
			SDL_RenderPresent(renderer);
		}
	}

	free_textures();
	SDL_close();

	return 0;
}