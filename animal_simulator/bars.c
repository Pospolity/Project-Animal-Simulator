#include "bars.h"

void load_need_bars_static_text_textures(struct bar * hungerBar, struct bar * thirstBar, struct bar * energyBar, struct bar * funBar)
{
	SDL_Color textColor = { BLACK_RGB_COLOR };
	texture_LoadFromRenderedText(&(hungerBar->titleTextTexture), "Hunger", textColor, font);
	texture_LoadFromRenderedText(&(thirstBar->titleTextTexture), "Thirst", textColor, font);
	texture_LoadFromRenderedText(&(energyBar->titleTextTexture), "Energy", textColor, font);
	texture_LoadFromRenderedText(&(funBar->titleTextTexture),    "Fun",    textColor, font);
}

void render_need_bars(struct bar hungerBar, struct bar thirstBar, struct bar energyBar, struct bar funBar)
{
	render_bar(hungerBar, HUNGER_BAR_TEXT_TLCX, HUNGER_BAR_TEXT_TLCY, NEED_BAR_WIDTH, NEED_BAR_HEIGHT, set_needBar_filling_color(hungerBar.currentValue, hungerBar.maxValue));
	render_bar(thirstBar, THIRST_BAR_TEXT_TLCX, THIRST_BAR_TEXT_TLCY, NEED_BAR_WIDTH, NEED_BAR_HEIGHT, set_needBar_filling_color(thirstBar.currentValue, thirstBar.maxValue));
	render_bar(energyBar, ENERGY_BAR_TEXT_TLCX, ENERGY_BAR_TEXT_TLCY, NEED_BAR_WIDTH, NEED_BAR_HEIGHT, set_needBar_filling_color(energyBar.currentValue, energyBar.maxValue));
	render_bar(funBar,    FUN_BAR_TEXT_TLCX,    FUN_BAR_TEXT_TLCY,    NEED_BAR_WIDTH, NEED_BAR_HEIGHT, set_needBar_filling_color(funBar.currentValue,	 funBar.maxValue));
}

void render_bar(struct bar bar, int x, int y, int w, int h, struct RGBAColor color)
{
	// RENDERING BAR TITLE
	SDL_Rect renderQuad = { x, y, bar.titleTextTexture.width, bar.titleTextTexture.height };
	SDL_RenderCopy(renderer, bar.titleTextTexture.texture, NULL, &renderQuad);

	// RENDERING BAR BORDER
	SDL_Rect_Set(&renderQuad, x, y + BAR_TEXT_SPACE_HEIGHT, w, h);
	SDL_SetRenderDrawColor(renderer, BAR_BORDER_RGBA_COLOR);
	SDL_RenderDrawRect(renderer, &renderQuad);

	// RENDERING BAR FILLING
	double percentFilled = (double)(bar.currentValue - bar.minValue) / bar.maxValue;
	SDL_Rect_Set(&renderQuad, x, y + BAR_TEXT_SPACE_HEIGHT, (int)(percentFilled * w), h);
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	SDL_RenderFillRect(renderer, &renderQuad);

	// RENDERING TEXT INSIDE BAR
	SDL_Color textColor = { BLACK_RGB_COLOR };
	char barValuesText[MAX_BAR_VALUES_TEXT_SIZE];
	snprintf(barValuesText, MAX_BAR_VALUES_TEXT_SIZE, "%d/%d", bar.currentValue, bar.maxValue);
	texture_LoadFromRenderedText(&(bar.valueTextTexture), barValuesText, textColor, font);
	SDL_Rect_Set(&renderQuad, x, y + BAR_TEXT_SPACE_HEIGHT, bar.valueTextTexture.width, bar.valueTextTexture.height);
	SDL_RenderCopy(renderer, bar.valueTextTexture.texture, NULL, &renderQuad); // call of this function here causes weird acting of memory allocation. Process memory rise in steps to some point and stays on that
	texture_Free(&(bar.valueTextTexture)); // we need to free this texture here, because texture_LoadFromRenderedText uses local copy of the bar and consequently assigns created texture to the pointer, which is deleted after function render_need_bar finishes
}

struct RGBAColor set_needBar_filling_color(int currentValue, int maxValue)
{
	if (currentValue < 0.15 * maxValue)
		return (struct RGBAColor) { NEED_BAR_RGBA_COLOR_DANGER };
	else if (currentValue < 0.30 * maxValue)
		return (struct RGBAColor) { NEED_BAR_RGBA_COLOR_WARNING };
	else if (currentValue < 0.75 * maxValue)
		return (struct RGBAColor) { NEED_BAR_RGBA_COLOR_NORMAL };
	else if (currentValue < 0.90 * maxValue)
		return (struct RGBAColor) { NEED_BAR_RGBA_COLOR_GOOD };
	else
		return (struct RGBAColor) { NEED_BAR_RGBA_COLOR_PERFECT };
}
