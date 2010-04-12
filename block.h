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

int collision(Block * block, Field field);
void freeze_block(Block * block, Field field);
void move_block(Block * block, int dx, int dy, Field field);
void rotate_block(Block * block, Field field);
void drop_block(Block * block, Field field);
void draw_block_destination(SDL_Surface * surface, Block block, Field field);

#endif

