#include "need_bars.h"

void load_need_bars_static_text_textures(struct needBar * hungerBar, struct needBar * thirstBar, struct needBar * energyBar, struct needBar * funBar)
{
	SDL_Color textColor = { 0, 0, 0 };
	texture_LoadFromRenderedText(&(hungerBar->titleTextTexture), "Hunger", textColor);
	texture_LoadFromRenderedText(&(thirstBar->titleTextTexture), "Thirst", textColor);
	texture_LoadFromRenderedText(&(energyBar->titleTextTexture), "Energy", textColor);
	texture_LoadFromRenderedText(&(funBar->titleTextTexture), "Fun", textColor);
}

void render_need_bars(struct needBar hungerBar, struct needBar thirstBar, struct needBar energyBar, struct needBar funBar)
{
	render_need_bar(hungerBar, HUNGER_BAR_TEXT_TLCX, HUNGER_BAR_TEXT_TLCY);
	render_need_bar(thirstBar, THIRST_BAR_TEXT_TLCX, THIRST_BAR_TEXT_TLCY);
	render_need_bar(energyBar, ENERGY_BAR_TEXT_TLCX, ENERGY_BAR_TEXT_TLCY);
	render_need_bar(funBar, FUN_BAR_TEXT_TLCX, FUN_BAR_TEXT_TLCY);
}

void render_need_bar(struct needBar needBar, int x, int y)
{
	// RENDERING NEED BAR TITLE
	SDL_Rect renderQuad = { x, y, needBar.titleTextTexture.width, needBar.titleTextTexture.height };
	SDL_RenderCopy(renderer, needBar.titleTextTexture.texture, NULL, &renderQuad);
	// RENDERING NEED BAR BORDER
	SDL_Rect_Set(&renderQuad, x, y + NEED_BAR_TEXT_SPACE_HEIGHT, NEED_BAR_WIDTH, NEED_BAR_HEIGHT);
	SDL_SetRenderDrawColor(renderer, NEED_BAR_BORDER_RGBA_COLOR);
	SDL_RenderDrawRect(renderer, &renderQuad);
	// RENDERING NEED BAR FILLING
	double percentFilled = (double)needBar.currentValue / needBar.maxValue;
	SDL_Rect_Set(&renderQuad, x, y + NEED_BAR_TEXT_SPACE_HEIGHT, (int)(percentFilled * NEED_BAR_WIDTH), NEED_BAR_HEIGHT);
	SDL_SetRenderDrawColor(renderer, NEED_BAR_RGBA_COLOR_FILLING);
	SDL_RenderFillRect(renderer, &renderQuad);
	// RENDERING TEXT INSIDE NEED BAR
	SDL_Color textColor = { 0, 0, 0 };
	char barValuesText[MAX_BAR_VALUES_TEXT_SIZE];
	snprintf(barValuesText, MAX_BAR_VALUES_TEXT_SIZE, "%d/%d", needBar.currentValue, needBar.maxValue);
	texture_LoadFromRenderedText(&(needBar.valueTextTexture), barValuesText, textColor);
	SDL_Rect_Set(&renderQuad, x, y + NEED_BAR_TEXT_SPACE_HEIGHT, needBar.valueTextTexture.width, needBar.valueTextTexture.height);
	SDL_RenderCopy(renderer, needBar.valueTextTexture.texture, NULL, &renderQuad); // call of this function here causes weird acting of memory allocation. Process memory rise in steps to some point and stays on that
	texture_Free(&(needBar.valueTextTexture)); // we need to free this texture here, because texture_LoadFromRenderedText uses local copy of the needBar and consequently assigns created texture to the pointer, which is deleted after function render_need_bar finishes
}