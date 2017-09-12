#include "buttons.h"

void button_HandleMouseEvents(struct button * button, SDL_Event * e, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
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

void handle_image_buttons_mouse_events(struct imageButton imageButtons[], SDL_Event * e) {
	for (int i = 0; i < NUMBER_OF_IMAGE_BUTTONS; i++)
		imageButton_HandleMouseEvent(&imageButtons[i], e);
}

void imageButton_HandleMouseEvent(struct imageButton * button, SDL_Event * e) {
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		int inside = TRUE;
		int currentButtonState = button->buttonState;
		if (currentButtonState == IB_CLICKED)
			currentButtonState = IB_HIGHLIGHTED; // IB_CLICKED doesn't have its own texture so we treat it, as it was IB_HIGHLIGHTED (because we need dimensions of textures for different button states)

		if (x < button->X)
			inside = FALSE;
		else if (x > button->X + button->imageTextures[currentButtonState].width)
			inside = FALSE;
		else if (y < button->Y)
			inside = FALSE;
		else if (y > button->Y + button->imageTextures[currentButtonState].height)
			inside = FALSE;

		if (!inside)
			button->buttonState = IB_INACTIVE;
		else {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				button->buttonState = IB_HIGHLIGHTED;
				break;
			case SDL_MOUSEBUTTONDOWN:
				button->buttonState = IB_CLICKED;
				break;
			case SDL_MOUSEBUTTONUP:
				button->buttonState = IB_HIGHLIGHTED;
				break;
			}
		}
	}
}

void switch_button_state(struct button button, int x, int y, int w, int h, int leftTextPadding, int topTextPadding)
{
	switch (button.buttonState) {
	case B_INACTIVE:
		render_static_button(button.buttonTextTexture, x, y, w, h, leftTextPadding, topTextPadding, DEFAULT_B_RGBA_COLOR_INACTIVE); break;
	case B_HIGHLIGHTED:
		render_static_button(button.buttonTextTexture, x, y, w, h, leftTextPadding, topTextPadding, DEFAULT_B_RGBA_COLOR_HIGHLIGHTED ); break;
	case B_ACTIVE:
		render_static_button(button.buttonTextTexture, x, y, w, h, leftTextPadding, topTextPadding, DEFAULT_B_RGBA_COLOR_ACTIVE); break;
	}
}

void render_static_buttons(struct button shopButton, struct button gamesButton, struct button saveButton, struct button exitButton)
{
		switch_button_state(shopButton, SHOP_B_TLCX, SHOP_B_TLCY, SHOP_B_WIDTH, SHOP_B_HEIGHT, SHOP_B_LEFT_TEXT_PADDING, SHOP_B_TOP_TEXT_PADDING);
		switch_button_state(gamesButton, GAMES_B_TLCX, GAMES_B_TLCY, GAMES_B_WIDTH, GAMES_B_HEIGHT, GAMES_B_LEFT_TEXT_PADDING, GAMES_B_TOP_TEXT_PADDING);
		switch_button_state(saveButton, SAVE_B_TLCX, SAVE_B_TLCY, SAVE_B_WIDTH, SAVE_B_HEIGHT, SAVE_B_LEFT_TEXT_PADDING, SAVE_B_TOP_TEXT_PADDING);
		switch_button_state(exitButton, EXIT_B_TLCX, EXIT_B_TLCY, EXIT_B_WIDTH, EXIT_B_HEIGHT, EXIT_B_LEFT_TEXT_PADDING, EXIT_B_TOP_TEXT_PADDING);
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
	texture_LoadFromRenderedText(&(shopButton->buttonTextTexture), "Shop", textColor, font);
	texture_LoadFromRenderedText(&(gamesButton->buttonTextTexture), "Games", textColor, font);
	texture_LoadFromRenderedText(&(saveButton->buttonTextTexture), "Save", textColor, font);
	texture_LoadFromRenderedText(&(exitButton->buttonTextTexture), "Exit", textColor, font);
}

int load_character_window_buttons_textures(struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS])
{
	int success = TRUE;
	char path[MAX_FILE_PATH_LENGTH];
	char constPath[] = "media/image_buttons/";
	for (int i = 0; i < NUMBER_OF_IMAGE_BUTTONS; i++) {
		sprintf_s(path, MAX_FILE_PATH_LENGTH, "%s%d.png", constPath, i);
		imageButtons[i].imageTextures[IB_INACTIVE] = texture_LoadFromImage(path);
		sprintf_s(path, MAX_FILE_PATH_LENGTH, "%s%dh.png", constPath, i);
		imageButtons[i].imageTextures[IB_HIGHLIGHTED] = texture_LoadFromImage(path);
		if (imageButtons[i].imageTextures[IB_INACTIVE].texture == NULL || imageButtons[i].imageTextures[IB_HIGHLIGHTED].texture == NULL) {
			success = FALSE;
			break;
		}
		set_image_button_tlcs(&imageButtons[i], i);
		imageButtons[i].buttonState = IB_INACTIVE;
	}
	return success;
}

void render_character_window_image_buttons(struct imageButton imageButtons[NUMBER_OF_IMAGE_BUTTONS])
{
	for (int i = 0; i < NUMBER_OF_IMAGE_BUTTONS; i++) {
		struct imageButton button = imageButtons[i];
		switch (button.buttonState) {
		case IB_INACTIVE:
			render_character_window_image_button(button.imageTextures[IB_INACTIVE], button.X, button.Y); break;
		case IB_CLICKED: // IB_CLICKED doesn't have its own texture so we show it, as it was IB_HIGHLIGHTED
		case IB_HIGHLIGHTED:
			render_character_window_image_button(button.imageTextures[IB_HIGHLIGHTED], button.X, button.Y); break;
		}
	}
}

void render_character_window_image_button(struct texture imageTexture, int x, int y)
{
	SDL_Rect renderQuad = { x, y, imageTexture.width, imageTexture.height };
	SDL_RenderCopy(renderer, imageTexture.texture, NULL, &renderQuad);
}

void set_image_button_tlcs(struct imageButton * imageButton, enum imageButtons currentButton)
{
	switch (currentButton) {
	case SLEEP_B: imageButton->X = SLEEP_B_TLCX; imageButton->Y = SLEEP_B_TLCY; break;
	case FOOD_B: imageButton->X = FOOD_B_TLCX; imageButton->Y = FOOD_B_TLCY; break;
	case DRINKS_B: imageButton->X = DRINKS_B_TLCX; imageButton->Y = DRINKS_B_TLCY; break;
	case TOY_B: imageButton->X = TOY_B_TLCX; imageButton->Y = TOY_B_TLCY; break;
	}
}