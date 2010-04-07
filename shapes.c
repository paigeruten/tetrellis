#include <stdlib.h>
#include "SDL/SDL.h"
#include "shapes.h"

int shapes[NUM_SHAPES][NUM_ROTATIONS][SHAPE_HEIGHT][SHAPE_WIDTH] = {
  // I
  {
    {
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,1 }
    },
    {
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,1 }
    }
  },

  // J
  {
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 0,0,1,0 }
    }
  },

  // L
  {
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,0,1,0 },
      { 1,1,1,0 }
    }
  },

  // S
  {
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,1,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,1,0 },
      { 1,1,0,0 }
    }
  },

  // Z
  {
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 0,1,1,0 }
    }
  },

  // T
  {
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,1,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,0,0 },
      { 0,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 0,1,0,0 },
      { 1,1,1,0 }
    },
    {
      { 0,0,0,0 },
      { 1,0,0,0 },
      { 1,1,0,0 },
      { 1,0,0,0 }
    }
  },

  // O
  {
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    },
    {
      { 0,0,0,0 },
      { 0,0,0,0 },
      { 1,1,0,0 },
      { 1,1,0,0 }
    }
  }
};

void draw_shape(SDL_Surface * surface, int x, int y, int shape, int rot) {
  int tile_x, tile_y;

  SDL_Rect tile;
  tile.w = TILE_WIDTH;
  tile.h = TILE_HEIGHT;

  for (tile_x = 0; tile_x < SHAPE_WIDTH; tile_x++) {
    for (tile_y = 0; tile_y < SHAPE_HEIGHT; tile_y++) {
      if (shapes[shape][rot][tile_y][tile_x] == 1) {
        tile.x = x + tile_x * TILE_WIDTH;
        tile.y = y + tile_y * TILE_HEIGHT;
        SDL_FillRect(surface, &tile, shape);
      }
    }
  }
}

void draw_shape_outline(SDL_Surface * surface, int x, int y, int shape, int rot) {
  int tile_x, tile_y;

  SDL_Rect line;

  for (tile_x = 0; tile_x < SHAPE_WIDTH; tile_x++) {
    for (tile_y = 0; tile_y < SHAPE_HEIGHT; tile_y++) {
      if (shapes[shape][rot][tile_y][tile_x] == 1) {
        // top border
        if (tile_y == 0 || shapes[shape][rot][tile_y - 1][tile_x] == 0) {
          line.x = x + tile_x * TILE_WIDTH;
          line.y = y + tile_y * TILE_HEIGHT;
          line.w = TILE_WIDTH;
          line.h = 1;
          SDL_FillRect(surface, &line, shape);
        }

        // bottom border
        if (tile_y == SHAPE_HEIGHT - 1 || shapes[shape][rot][tile_y + 1][tile_x] == 0) {
          line.x = x + tile_x * TILE_WIDTH;
          line.y = y + (tile_y + 1) * TILE_HEIGHT;
          line.w = TILE_WIDTH;
          line.h = 1;
          SDL_FillRect(surface, &line, shape);
        }

        // left border
        if (tile_x == 0 || shapes[shape][rot][tile_y][tile_x - 1] == 0) {
          line.x = x + tile_x * TILE_WIDTH;
          line.y = y + tile_y * TILE_HEIGHT;
          line.w = 1;
          line.h = TILE_HEIGHT;
          SDL_FillRect(surface, &line, shape);
        }

        // right border
        if (tile_x == SHAPE_WIDTH - 1 || shapes[shape][rot][tile_y][tile_x + 1] == 0) {
          line.x = x + (tile_x + 1) * TILE_WIDTH;
          line.y = y + tile_y * TILE_HEIGHT;
          line.w = 1;
          line.h = TILE_HEIGHT;
          SDL_FillRect(surface, &line, shape);
        }
      }
    }
  }
}

int real_shape_width(int shape, int rot) {
  int max_width = 0;
  int x, y;

  for (x = 0; x < SHAPE_WIDTH; x++) {
    for (y = 0; y < SHAPE_HEIGHT; y++) {
      if (shapes[shape][rot][y][x]) {
        max_width = x;
      }
    }
  }

  return max_width + 1;
}

int real_shape_height(int shape, int rot) {
  int max_height = SHAPE_HEIGHT;
  int x, y;

  for (y = SHAPE_HEIGHT; y >= 0; y--) {
    for (x = 0; x < SHAPE_WIDTH; x++) {
      if (shapes[shape][rot][y][x]) {
        max_height = y;
      }
    }
  }

  return SHAPE_HEIGHT - max_height;
}

int random_shape(void) {
  return rand() % NUM_SHAPES;
}

