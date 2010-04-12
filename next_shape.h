#ifndef _next_shape_h
#define _next_shape_h

#include "main.h"
#include "shapes.h"
#include "field.h"

#define NEXT_SHAPE_X (FIELD_X + FIELD_WIDTH * TILE_WIDTH + TILE_WIDTH)
#define NEXT_SHAPE_Y (FIELD_Y)
#define NEXT_SHAPE_WIDTH (SHAPE_WIDTH + 1)
#define NEXT_SHAPE_HEIGHT (SHAPE_HEIGHT + 1)
#define NEXT_SHAPE_BORDER 2

void draw_next_shape(SDL_Surface * surface, int shape);

#endif

