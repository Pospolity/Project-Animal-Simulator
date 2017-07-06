#include "buttons.h"

void button_HandleMouseEvents(struct button * button, SDL_Event * e, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		int inside = TRUE;

		if (x < buttonX)
			inside = FALSE;
		else if (x > buttonX + buttonWidth)
			inside = FALSE;
		else if (y < buttonY)
			inside = FALSE;
		else if (y > buttonY + buttonHeight)
			inside = FALSE;

		if (!inside)
			button->buttonState = B_INACTIVE;
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				button->buttonState = B_HIGHLIGHTED;
				break;
			case SDL_MOUSEBUTTONDOWN:
				button->buttonState = B_ACTIVE;
				break;
			case SDL_MOUSEBUTTONUP:
				button->buttonState = B_HIGHLIGHTED;
				break;
			}
		}
	}
}

void render_static_buttons(struct button shopButton, struct button gamesButton, struct button saveButton, struct button exitButton)
{
	switch (shopButton.buttonState) {
	case B_INACTIVE:
		render_static_button(shopButton.buttonTextTexture, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT, SHOP_B_LEFT_TEXT_PADDING, SHOP_B_TOP_TEXT_PADDING, SHOP_B_RGBA_COLOR_INACTIVE); break;
	case B_HIGHLIGHTED:
		render_static_button(shopButton.buttonTextTexture, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT, SHOP_B_LEFT_TEXT_PADDING, SHOP_B_TOP_TEXT_PADDING, SHOP_B_RGBA_COLOR_HIGHLIGHTED); break;
	case B_ACTIVE:
		render_static_button(shopButton.buttonTextTexture, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT, SHOP_B_LEFT_TEXT_PADDING, SHOP_B_TOP_TEXT_PADDING, SHOP_B_RGBA_COLOR_ACTIVE); break;
	}
	switch (gamesButton.buttonState) {
	case B_INACTIVE:
		render_static_button(gamesButton.buttonTextTexture, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT, GAMES_B_LEFT_TEXT_PADDING, GAMES_B_TOP_TEXT_PADDING, GAMES_B_RGBA_COLOR_INACTIVE); break;
	case B_HIGHLIGHTED:
		render_static_button(gamesButton.buttonTextTexture, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT, GAMES_B_LEFT_TEXT_PADDING, GAMES_B_TOP_TEXT_PADDING, GAMES_B_RGBA_COLOR_HIGHLIGHTED); break;
	case B_ACTIVE:
		render_static_button(gamesButton.buttonTextTexture, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT, GAMES_B_LEFT_TEXT_PADDING, GAMES_B_TOP_TEXT_PADDING, GAMES_B_RGBA_COLOR_ACTIVE); break;
	}
	switch (saveButton.buttonState) {
	case B_INACTIVE:
		render_static_button(shopButton.buttonTextTexture, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT, SAVE_B_LEFT_TEXT_PADDING, SAVE_B_TOP_TEXT_PADDING, SAVE_B_RGBA_COLOR_INACTIVE); break;
	case B_HIGHLIGHTED:
		render_static_button(shopButton.buttonTextTexture, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT, SAVE_B_LEFT_TEXT_PADDING, SAVE_B_TOP_TEXT_PADDING, SAVE_B_RGBA_COLOR_HIGHLIGHTED); break;
	case B_ACTIVE:
		render_static_button(shopButton.buttonTextTexture, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT, SAVE_B_LEFT_TEXT_PADDING, SAVE_B_TOP_TEXT_PADDING, SAVE_B_RGBA_COLOR_ACTIVE); break;
	}
	switch (exitButton.buttonState) {
	case B_INACTIVE:
		render_static_button(exitButton.buttonTextTexture, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT, EXIT_B_LEFT_TEXT_PADDING, EXIT_B_TOP_TEXT_PADDING, EXIT_B_RGBA_COLOR_INACTIVE); break;
	case B_HIGHLIGHTED:
		render_static_button(exitButton.buttonTextTexture, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT, EXIT_B_LEFT_TEXT_PADDING, EXIT_B_TOP_TEXT_PADDING, EXIT_B_RGBA_COLOR_HIGHLIGHTED); break;
	case B_ACTIVE:
		render_static_button(exitButton.buttonTextTexture, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT, EXIT_B_LEFT_TEXT_PADDING, EXIT_B_TOP_TEXT_PADDING, EXIT_B_RGBA_COLOR_ACTIVE); break;
	}
}

void render_static_button(struct texture staticButtonTextTexture, int x, int y, int w, int h, int leftTextPadding, int topTextPadding, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect renderQuad = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &renderQuad);
	SDL_Rect_Set(&renderQuad, x + leftTextPadding, y + topTextPadding, staticButtonTextTexture.width, staticButtonTextTexture.height);
	SDL_RenderCopy(renderer, staticButtonTextTexture.texture, NULL, &renderQuad);
}

void load_static_buttons_text_textures(struct button * shopButton, struct button * gamesButton, struct button * saveButton, struct button * exitButton)
{
	SDL_Color textColor = { 0, 0, 0 };
	texture_LoadFromRenderedText(&(shopButton->buttonTextTexture), "Shop", textColor);
	texture_LoadFromRenderedText(&(gamesButton->buttonTextTexture), "Games", textColor);
	texture_LoadFromRenderedText(&(saveButton->buttonTextTexture), "Save", textColor);
	texture_LoadFromRenderedText(&(exitButton->buttonTextTexture), "Exit", textColor);
}