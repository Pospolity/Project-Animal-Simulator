#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

#include "SDL_management_functions.h"

struct texture // data fields: { SDL_Texture* texture; int width; int height; }
{
	SDL_Texture* texture;
	int width;
	int height;
};

int load_textures(void);
void free_textures(void);
void render_static_windows(struct texture windowText);
void render_static_buttons(void);
void load_static_windows(struct texture * windowText);
void load_static_buttons(void);
void texture_Free(struct texture * textureToFree);
void texture_LoadFromRenderedText(struct texture * textTexture, char * textString, SDL_Color textColor);
void SDL_Rect_Set(SDL_Rect * sdl_rect, int x, int y, int w, int h);

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

void render_static_windows(struct texture windowText)
{
	// render active events window
	SDL_Rect renderQuad = { ACTIVE_EVENTS_WINDOW_TLCX, ACTIVE_EVENTS_WINDOW_TLCY, ACTIVE_EVENTS_WINDOW_WIDTH, ACTIVE_EVENTS_WINDOW_HEIGHT };
	SDL_SetRenderDrawColor(renderer, ACTIVE_EVENTS_WINDOW_RGBA_COLOR);
	SDL_RenderFillRect(renderer, &renderQuad);
	SDL_Rect_Set(&renderQuad, 135, 10, windowText.width, windowText.height);
	SDL_RenderCopy(renderer, windowText.texture, NULL, &renderQuad);
	// render next static windows...
}

void load_static_windows(struct texture * windowText) 
{
	SDL_Color textColor = { 0, 0, 0 };
	texture_LoadFromRenderedText(windowText, "Active Events", textColor);

}

void render_static_buttons(void)
{
	;//
	//
}

void load_static_buttons(void) 
{
	;//
}

void texture_Free(struct texture * textureToFree)
{
	if (textureToFree->texture != NULL) { //at first check if the texture exists
		SDL_DestroyTexture(textureToFree->texture);
		textureToFree->texture = NULL;
		textureToFree->height = 0;
		textureToFree->width = 0;
	}
}

void texture_LoadFromRenderedText(struct texture * textTexture, char * textString, SDL_Color textColor)
{
	texture_Free(textTexture);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textString, textColor);
	if (textSurface != NULL) {
		textTexture->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture->texture != NULL) {
			textTexture->width = textSurface->w;
			textTexture->height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void SDL_Rect_Set(SDL_Rect * sdl_rect, int x, int y, int w, int h) {
	sdl_rect->x = x;
	sdl_rect->y = y;
	sdl_rect->w = w;
	sdl_rect->h = h;
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
		font = TTF_OpenFont("funnypages.ttf", 14); //setting the font
		if (font == NULL) {
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		}
		// MAKE A STATIC WINDOW TEXT
		struct texture windowText = { NULL, 0, 0 };
		load_static_windows(&windowText);
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) { //Handling events on queue
				if (e.type == SDL_QUIT) //User requests quit by clicking the standard windows' close button
					quit = TRUE;
			}

			//Clearing the screen
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);

			render_static_windows(windowText);
			render_static_buttons();

			//Updating the screen
			SDL_RenderPresent(renderer);
		}
	}

	free_textures();
	SDL_close();

	return 0;
}