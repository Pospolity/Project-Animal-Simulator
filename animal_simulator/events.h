#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"

struct Event {
	char			message[MAX_EVENT_MESSAGE_LENGTH];
	struct texture	messageTexture;
};

void render_text_events_window	(struct Event events[], int newest);
void addEvent					(struct Event events[], int * newest, char messageText[]);