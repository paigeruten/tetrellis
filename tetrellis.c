#include "SDL/SDL.h"
#include "tetrellis.h"

#define SPEED 1000 // will be variable eventually

Block current_block;
int next_shape;

int collision(int shape, int rot, int x, int y) {
  int i, j;

  // first check for field boundaries
  if (x < 0 || y < 0 || x + real_shape_width(shape, rot) > FIELD_WIDTH || y >= FIELD_HEIGHT) {
    return 1;
  }

  // now for tiles
  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[shape][rot][i][j]) {
        if (field[y + i][x + j] != -1) {
          return 1;
        }
      }
    }
  }

  return 0;
}

void freeze_block(void) {
  if (current_block.shape == -1) return;

  int i, j;

  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[current_block.shape][current_block.rot][i][j]) {
        field[current_block.y + i][current_block.x + j] = current_block.shape;
      }
    }
  }

  current_block.shape = -1;
  next_shape = random_shape();
}

// returns true if block gets frozen
int move_block(int dx, int dy) {
  if (current_block.shape == -1) return 0;

  if (collision(current_block.shape, current_block.rot, current_block.x + dx, current_block.y + dy)) {
    // if the block is moving down, then it should come to rest.
    // otherwise just do nothing.
    if (dy) {
      freeze_block();
      return 1;
    }
  } else {
    current_block.x += dx;
    current_block.y += dy;
  }

  return 0;
}

void rotate_block(void) {
  if (current_block.shape == -1) return;

  int new_rot = (current_block.rot + 1) % NUM_ROTATIONS;

  if (!collision(current_block.shape, new_rot, current_block.x, current_block.y)) {
    current_block.rot = new_rot;
  }
}

void drop_block(void) {
  if (current_block.shape == -1) return;

  while (!move_block(0, 1))
    ;
}

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit = 0;
  long last_tick;

  clear_field();

  current_block.shape = -1;
  next_shape = random_shape();
  last_tick = SDL_GetTicks();

  while (!quit) {
    // handle input
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_UP) {
            rotate_block();
          } else if (event.key.keysym.sym == SDLK_LEFT) {
            move_block(-1, 0);
          } else if (event.key.keysym.sym == SDLK_RIGHT) {
            move_block(1, 0);
          } else if (event.key.keysym.sym == SDLK_DOWN) {
            move_block(0, 1);
            last_tick = SDL_GetTicks();
          } else if (event.key.keysym.sym == SDLK_SPACE) {
            drop_block();
          }
          break;

        case SDL_QUIT:
          quit = 1;
          break;

        default:
          break;
      }
    }

    // update gamestate
    if (current_block.shape == -1) {
      current_block.shape = next_shape;
      current_block.rot = 0;
      current_block.x = (FIELD_WIDTH - SHAPE_WIDTH) / 2;
      current_block.y = 0;
    } else {
      if (SDL_GetTicks() - last_tick > SPEED) {
        move_block(0, 1);
        last_tick = SDL_GetTicks();
      }
    }

    // render to screen
    draw_field(surface);

    if (current_block.shape != -1) {
      draw_shape(surface, FIELD_X + current_block.x * TILE_WIDTH, FIELD_Y + current_block.y * TILE_HEIGHT, current_block.shape, current_block.rot);
    }

    SDL_UpdateRect(surface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Delay(1);
  }
}



