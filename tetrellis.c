#include "SDL/SDL.h"
#include "tetrellis.h"

Block BLOCK_NULL = (Block){ SHAPE_NULL, 0, 0, 0 };

Block current_block;
int next_shape;
int speed;

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

void freeze_block(void) {
  if (NULL_BLOCK(current_block)) return;

  int i, j;

  for (i = 0; i < SHAPE_HEIGHT; i++) {
    for (j = 0; j < SHAPE_WIDTH; j++) {
      if (shapes[current_block.shape][current_block.rot][i][j]) {
        field_set(current_block.x + j, current_block.y + i, current_block.shape);
      }
    }
  }

  current_block = BLOCK_NULL;
}

void draw_next_shape(SDL_Surface * surface) {
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
             NEXT_SHAPE_X + (NEXT_SHAPE_WIDTH * TILE_WIDTH - real_shape_width(next_shape, 0) * TILE_WIDTH) / 2,
             NEXT_SHAPE_Y + (NEXT_SHAPE_HEIGHT - real_shape_height(next_shape, 0)) * TILE_HEIGHT / 2 - (SHAPE_HEIGHT - real_shape_height(next_shape, 0)) * TILE_HEIGHT,
             next_shape,
             0);
}

// returns true if block gets frozen
int move_block(int dx, int dy) {
  if (NULL_BLOCK(current_block)) return 0;

  Block new_block = current_block;
  new_block.x += dx;
  new_block.y += dy;

  if (collision(new_block)) {
    // if the block is moving down, then it should come to rest.
    // otherwise just do nothing.
    if (dy) {
      freeze_block();
      return 1;
    }
  } else {
    current_block = new_block;
  }

  return 0;
}

void rotate_block(void) {
  if (NULL_BLOCK(current_block)) return;

  Block new_block = current_block;
  new_block.rot = (current_block.rot + 1) % NUM_ROTATIONS;

  if (! collision(new_block)) {
    current_block = new_block;
  }
}

void draw_shape_destination(SDL_Surface * surface, Block block) {
  while (! collision(block)) {
    block.y++;
  }
  block.y--;

  draw_shape_outline(surface, FIELD_X + block.x * TILE_WIDTH, FIELD_Y + block.y * TILE_HEIGHT, block.shape, block.rot);
}

void drop_block(void) {
  if (NULL_BLOCK(current_block)) return;

  while (! move_block(0, 1))
    ;
}

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit;
  long last_tick;
  int lines, lines_cleared;
  int level;

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
    if (NULL_BLOCK(current_block)) {
      current_block.shape = next_shape;
      current_block.rot = 0;
      current_block.x = (FIELD_WIDTH - SHAPE_WIDTH) / 2;
      current_block.y = real_shape_height(current_block.shape, current_block.rot) - SHAPE_HEIGHT;

      next_shape = random_shape();
    } else {
      if (SDL_GetTicks() - last_tick > speed) {
        move_block(0, 1);
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
    draw_next_shape(surface);

    if (! NULL_BLOCK(current_block)) {
      draw_shape(surface, FIELD_X + current_block.x * TILE_WIDTH, FIELD_Y + current_block.y * TILE_HEIGHT, current_block.shape, current_block.rot);
      draw_shape_destination(surface, current_block);
    }

    SDL_UpdateRect(surface, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Delay(1);
  }
}



