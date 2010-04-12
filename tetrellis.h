#ifndef _tetrellis_h
#define _tetrellis_h

#include "main.h"
#include "shapes.h"
#include "field.h"

#define INITIAL_SPEED 1000
#define INCREASE_SPEED_BY 50
#define LINES_NEEDED_FOR_NEXT_LEVEL 20

#define NEXT_SHAPE_X (FIELD_X + FIELD_WIDTH * TILE_WIDTH + TILE_WIDTH)
#define NEXT_SHAPE_Y (FIELD_Y)
#define NEXT_SHAPE_WIDTH (SHAPE_WIDTH + 1)
#define NEXT_SHAPE_HEIGHT (SHAPE_HEIGHT + 1)
#define NEXT_SHAPE_BORDER 2

typedef struct {
  int shape;
  int rot;
  int x;
  int y;
} Block;

#define NULL_BLOCK(x) (NULL_SHAPE((x).shape))

int collision(Block block);
Block freeze_block(Block block);
void draw_next_shape(SDL_Surface * surface, int shape);
Block move_block(Block block, int dx, int dy);
Block rotate_block(Block block);
Block drop_block(Block block);
void tetrellis(SDL_Surface * surface);

#endif

