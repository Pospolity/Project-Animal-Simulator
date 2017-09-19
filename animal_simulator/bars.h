#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"
#include "commons.h"

struct bar
{
	struct texture	titleTextTexture;
	struct texture	valueTextTexture;
	int				minValue;
	int				maxValue;
	int				currentValue;
};

void			render_bar							(struct bar bar, int x, int y, int w, int h, struct RGBAColor color);
void			render_need_bars					(struct bar hungerBar, struct bar thirstBar, struct bar energyBar, struct bar funBar);
void			load_need_bars_static_text_textures	(struct bar * hungerBar, struct bar * thirstBar, struct bar * energyBar, struct bar * funBar);
struct RGBAColor set_needBar_filling_color			(int currentValue, int maxValue);