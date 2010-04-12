#ifndef _block_h
#define _block_h

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

int collision(Block block);
Block freeze_block(Block block);
Block move_block(Block block, int dx, int dy);
Block rotate_block(Block block);
Block drop_block(Block block);

#endif

