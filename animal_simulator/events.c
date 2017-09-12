#include "events.h"

void addEvent(struct Event events[], int * newest, char messageText[])
{
	struct Event event = { "", NULL }; // empty event
	strncpy_s(event.message, MAX_EVENT_MESSAGE_LENGTH, messageText, MAX_EVENT_MESSAGE_LENGTH - 1);
	event.message[MAX_EVENT_MESSAGE_LENGTH - 1] = '\n';
	if (*newest == 5)
		*newest = 0;
	else
		(*newest)++;
	texture_Free(&events[*newest].messageTexture);
	texture_LoadFromRenderedText(&event.messageTexture, event.message, (SDL_Color) { 0, 0, 0 }, textEventsFont);
	events[*newest] = event;
};

void render_text_events_window(struct Event events[], int newest)
{
	SDL_Rect renderQuad = { TEXT_EVENTS_WINDOW_TLCX + 10, TEXT_EVENTS_WINDOW_TLCY + 5, TEXT_EVENTS_WINDOW_WIDTH - 20, TEXT_EVENTS_WINDOW_HEIGHT - 10 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &renderQuad);
	for (int i = 0; i < MAX_NUMBER_OF_EVENTS; i++) {
		struct Event currentEvent = events[(MAX_NUMBER_OF_EVENTS + (newest - i)) % MAX_NUMBER_OF_EVENTS];
		if (currentEvent.messageTexture.texture != NULL) {
			SDL_Rect_Set(&renderQuad, TEXT_EVENTS_WINDOW_TLCX + 20, TEXT_EVENTS_WINDOW_TLCY + 5 + (17 * i), currentEvent.messageTexture.width, currentEvent.messageTexture.height);
			SDL_RenderCopy(renderer, currentEvent.messageTexture.texture, NULL, &renderQuad);
		}
	}
};