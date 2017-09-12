#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

struct texture // data fields: { SDL_Texture* texture; int width; int height; }
{
	SDL_Texture* texture;
	int width;
	int height;
}; 
void texture_Free(struct texture * textureToFree);
void texture_LoadFromRenderedText(struct texture * textTexture, char * textString, SDL_Color textColor, TTF_Font * font);
struct texture texture_LoadFromImage(char * sourcePath);
