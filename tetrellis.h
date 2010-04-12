#ifndef _tetrellis_h
#define _tetrellis_h

#include "main.h"
#include "shapes.h"
#include "field.h"
#include "block.h"

#define INITIAL_SPEED 1000
#define INCREASE_SPEED_BY 50
#define LINES_NEEDED_FOR_NEXT_LEVEL 20

#define NEXT_SHAPE_X (FIELD_X + FIELD_WIDTH * TILE_WIDTH + TILE_WIDTH)
#define NEXT_SHAPE_Y (FIELD_Y)
#define NEXT_SHAPE_WIDTH (SHAPE_WIDTH + 1)
#define NEXT_SHAPE_HEIGHT (SHAPE_HEIGHT + 1)
#define NEXT_SHAPE_BORDER 2

void draw_next_shape(SDL_Surface * surface, int shape);
void draw_shape_destination(SDL_Surface * surface, Block block);
void tetrellis(SDL_Surface * surface);

#endif

