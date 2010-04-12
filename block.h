#ifndef _block_h
#define _block_h

#include "main.h"
#include "shapes.h"
#include "field.h"

typedef struct {
  int shape;
  int rot;
  int x;
  int y;
} Block;

#define BLOCK_NULL ((Block){ SHAPE_NULL, 0, 0, 0 })
#define NULL_BLOCK(x) (NULL_SHAPE((x).shape))

int collision(Block * block);
void freeze_block(Block * block);
void move_block(Block * block, int dx, int dy);
void rotate_block(Block * block);
void drop_block(Block * block);
void draw_block_destination(SDL_Surface * surface, Block block);

#endif

