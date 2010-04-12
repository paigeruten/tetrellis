#include "SDL/SDL.h"
#include "tetrellis.h"

void draw_next_shape(SDL_Surface * surface, int shape) {
  int i, j;
  SDL_Rect background;
  SDL_Rect border;

  border.x = NEXT_SHAPE_X - NEXT_SHAPE_BORDER;
  border.y = NEXT_SHAPE_Y - NEXT_SHAPE_BORDER;
  border.w = NEXT_SHAPE_WIDTH * TILE_WIDTH + NEXT_SHAPE_BORDER * 2;
  border.h = NEXT_SHAPE_HEIGHT * TILE_HEIGHT + NEXT_SHAPE_BORDER * 2;
  SDL_FillRect(surface, &border, COLOR_FIELD_BORDER);

  background = border;
  background.x += NEXT_SHAPE_BORDER;
  background.y += NEXT_SHAPE_BORDER;
  background.w -= NEXT_SHAPE_BORDER * 2;
  background.h -= NEXT_SHAPE_BORDER * 2;
  SDL_FillRect(surface, &background, COLOR_FIELD_BACKGROUND);

  draw_shape(surface,
             NEXT_SHAPE_X + (NEXT_SHAPE_WIDTH * TILE_WIDTH - real_shape_width(shape, 0) * TILE_WIDTH) / 2,
             NEXT_SHAPE_Y + (NEXT_SHAPE_HEIGHT - real_shape_height(shape, 0)) * TILE_HEIGHT / 2 - (SHAPE_HEIGHT - real_shape_height(shape, 0)) * TILE_HEIGHT,
             shape,
             0);
}

void draw_shape_destination(SDL_Surface * surface, Block block) {
  while (! collision(block)) {
    block.y++;
  }
  block.y--;

  draw_shape_outline(surface, FIELD_X + block.x * TILE_WIDTH, FIELD_Y + block.y * TILE_HEIGHT, block.shape, block.rot);
}

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit;
  long last_tick;
  int lines, lines_cleared;
  int level;
  Block current_block;
  int next_shape;
  int speed;

  clear_field();

  current_block = BLOCK_NULL;
  next_shape = random_shape();
  last_tick = SDL_GetTicks();
  speed = INITIAL_SPEED;
  lines_cleared = 0;
  quit = 0;
  level = 1;

  while (! quit) {
    // handle input
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_UP) {
            current_block = rotate_block(current_block);
          } else if (event.key.keysym.sym == SDLK_LEFT) {
            current_block = move_block(current_block, -1, 0);
          } else if (event.key.keysym.sym == SDLK_RIGHT) {
            current_block = move_block(current_block, 1, 0);
          } else if (event.key.keysym.sym == SDLK_DOWN) {
            current_block = move_block(current_block, 0, 1);
            last_tick = SDL_GetTicks();
          } else if (event.key.keysym.sym == SDLK_SPACE) {
            current_block = drop_block(current_block);
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
    if (NULL_BLOCK(current_block)) {
      current_block.shape = next_shape;
      current_block.rot = 0;
      current_block.x = (FIELD_WIDTH - SHAPE_WIDTH) / 2;
      current_block.y = real_shape_height(current_block.shape, current_block.rot) - SHAPE_HEIGHT;

      next_shape = random_shape();
    } else {
      if (SDL_GetTicks() - last_tick > speed) {
        current_block = move_block(current_block, 0, 1);
        last_tick = SDL_GetTicks();
      }
    }

    if (lines = clear_lines()) {
      int i;
      for (i = 0; i < lines; i++) {
        if ((lines_cleared + i) % LINES_NEEDED_FOR_NEXT_LEVEL == 0) {
          level++;
          speed -= INCREASE_SPEED_BY;
        }
      }

      lines_cleared += lines;

      // DEBUG
      printf("level = %d\nlines_cleared = %d\nspeed = %d\n\n", level, lines_cleared, speed);
    }

    if (game_over()) {
      quit = 1;
    }

    // render to screen
    draw_field(surface);
    draw_next_shape(surface, next_shape);

    if (! NULL_BLOCK(current_block)) {
      draw_shape(surface, FIELD_X + current_block.x * TILE_WIDTH, FIELD_Y + current_block.y * TILE_HEIGHT, current_block.shape, current_block.rot);
      draw_shape_destination(surface, current_block);
    }

    SDL_UpdateRect(surface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Delay(1);
  }
}



