#pragma once

#include "project_constants.h"
#include "project_libraries.h"
#include "project_global_variables.h"
#include "textures.h"

void render_static_windows(struct texture activeEventsWindowTextTexture, struct texture needsBarsWindowTextTexture, struct texture textEventsWindowTextTexture);
void render_static_window(struct texture staticWindowTextTexture, int x, int y, int w, int h, int leftTextPadding, int topTextPadding, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void load_static_windows_text_textures(struct texture * activeEventsWindowTextTexture, struct texture * needsBarsWindowTextTexture, struct texture * textEventsWindowTextTexture);
