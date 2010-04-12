#include "SDL/SDL.h"
#include "block.h"

int collision(Block block) {
  int i, j;

  // first check for field boundaries
  if (block.x < 0 || block.x + real_shape_width(block.shape, block.rot) > FIELD_WIDTH || block.y >= FIELD_HEIGHT) {
    return 1;
  }

  // now for tiles
  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[block.shape][block.rot][i][j]) {
        if (! NULL_SHAPE(field_get(block.x + j, block.y + i))) {
          return 1;
        }
      }
    }
  }

  return 0;
}

Block freeze_block(Block block) {
  if (NULL_BLOCK(block)) return;

  int i, j;

  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[block.shape][block.rot][i][j]) {
        field_set(block.x + j, block.y + i, block.shape);
      }
    }
  }

  return BLOCK_NULL;
}

Block move_block(Block block, int dx, int dy) {
  if (NULL_BLOCK(block)) return block;

  Block new_block = block;
  new_block.x += dx;
  new_block.y += dy;

  if (collision(new_block)) {
    // if the block is moving down, then it should come to rest.
    // otherwise just do nothing.
    if (dy) {
      return freeze_block(block);
    } else {
      return block;
    }
  } else {
    return new_block;
  }
}

Block rotate_block(Block block) {
  if (NULL_BLOCK(block)) return block;

  Block new_block = block;
  new_block.rot = (block.rot + 1) % NUM_ROTATIONS;

  if (collision(new_block)) {
    return block;
  } else {
    return new_block;
  }
}

Block drop_block(Block block) {
  if (NULL_BLOCK(block)) return block;

  while (! NULL_BLOCK(block)) {
    block = move_block(block, 0, 1);
  }

  return block;
}


