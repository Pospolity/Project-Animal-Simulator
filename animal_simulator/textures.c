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
struct texture texture_LoadFromImage(char * sourcePath)
{
	struct texture newTexture;
	SDL_Texture* newSDLTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(sourcePath);
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL_image Error: %s\n", sourcePath, IMG_GetError());
	else {
		newSDLTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newSDLTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", sourcePath, SDL_GetError());
		} else {
			newTexture.height = loadedSurface->h;
			newTexture.width = loadedSurface->w;
		}
		newTexture.texture = newSDLTexture; // if something gone wrong it will be set as NULL, so we can use it later to check if we can use this texture without causing unexpected error
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}