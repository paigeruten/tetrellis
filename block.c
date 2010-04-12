#include "SDL/SDL.h"
#include "block.h"

int collision(Block * block) {
  int i, j;

  // first check for field boundaries
  if (block->x < 0 || block->x + real_shape_width(block->shape, block->rot) > FIELD_WIDTH || block->y >= FIELD_HEIGHT) {
    return 1;
  }

  // now for tiles
  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[block->shape][block->rot][i][j]) {
        if (! NULL_SHAPE(field_get(block->x + j, block->y + i))) {
          return 1;
        }
      }
    }
  }

  return 0;
}

void freeze_block(Block * block) {
  if (NULL_BLOCK(*block)) return;

  int i, j;

  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[block->shape][block->rot][i][j]) {
        field_set(block->x + j, block->y + i, block->shape);
      }
    }
  }

  *block = BLOCK_NULL;
}

void move_block(Block * block, int dx, int dy) {
  if (NULL_BLOCK(*block)) return;

  Block new_block = *block;
  new_block.x += dx;
  new_block.y += dy;

  if (collision(&new_block)) {
    // if the block is moving down, then it should come to rest.
    // otherwise just do nothing.
    if (dy) {
      freeze_block(block);
    }
  } else {
    *block = new_block;
  }
}

void rotate_block(Block * block) {
  if (NULL_BLOCK(*block)) return;

  Block new_block = *block;
  new_block.rot = (block->rot + 1) % NUM_ROTATIONS;

  if (! collision(&new_block)) {
    *block = new_block;
  }
}

void drop_block(Block * block) {
  if (NULL_BLOCK(*block)) return;

  while (! NULL_BLOCK(*block)) {
    move_block(block, 0, 1);
  }
}

void draw_block_destination(SDL_Surface * surface, Block block) {
  while (! collision(&block)) {
    block.y++;
  }
  block.y--;

  draw_shape_outline(surface, FIELD_X + block.x * TILE_WIDTH, FIELD_Y + block.y * TILE_HEIGHT, block.shape, block.rot);
}

