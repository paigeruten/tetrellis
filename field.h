#ifndef _field_h
#define _field_h

#include "main.h"
#include "shapes.h"

#define FIELD_WIDTH 14
#define FIELD_HEIGHT 20

#define FIELD_X ((SCREEN_WIDTH - FIELD_WIDTH * TILE_WIDTH) / 2)
#define FIELD_Y ((SCREEN_HEIGHT - FIELD_HEIGHT * TILE_HEIGHT) / 2)

void draw_field(SDL_Surface * surface);
void clear_field(void);

#endif

