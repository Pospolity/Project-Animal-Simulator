#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"

int	 SDL_initialize	(void);
void SDL_close		(void);
void SDL_Rect_Set	(SDL_Rect * sdl_rect, int x, int y, int w, int h);