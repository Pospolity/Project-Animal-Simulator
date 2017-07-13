#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"

struct needBar
{
	struct texture titleTextTexture;
	struct texture valueTextTexture;
	int maxValue;
	int currentValue;
};

void render_need_bar(struct needBar needBar, int x, int y);
void render_need_bars(struct needBar hungerBar, struct needBar thirstBar, struct needBar energyBar, struct needBar funBar);
void load_need_bars_static_text_textures(struct needBar * hungerBar, struct needBar * thirstBar, struct needBar * energyBar, struct needBar * funBar);