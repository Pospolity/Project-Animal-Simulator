#include "textures.h"

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