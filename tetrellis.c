#include "SDL/SDL.h"
#include "tetrellis.h"

#define SPEED 1000 // will be variable eventually

Block current_block;
int next_shape;

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit = 0;
  int last_tick;

  clear_field();

  current_block.shape = -1;
  next_shape = random_shape();
  last_tick = SDL_GetTicks();

  while (!quit) {
    // handle input
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
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
        current_block.y++;
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



