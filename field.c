#include "SDL/SDL.h"
#include "field.h"

int field[FIELD_HEIGHT][FIELD_WIDTH];

void draw_field(SDL_Surface * surface) {
  int i, j;
  SDL_Rect tile;
  SDL_Rect border;

  border.x = FIELD_X - 1;
  border.y = FIELD_Y - 1;
  border.w = FIELD_WIDTH * TILE_WIDTH + 2;
  border.h = FIELD_HEIGHT * TILE_HEIGHT + 2;

  SDL_FillRect(surface, &border, 10);

  tile.w = TILE_WIDTH;
  tile.h = TILE_HEIGHT;

  for (i = 0; i < FIELD_HEIGHT; i++) {
    for (j = 0; j < FIELD_WIDTH; j++) {
      tile.x = FIELD_X + j * TILE_WIDTH;
      tile.y = FIELD_Y + i * TILE_HEIGHT;
      SDL_FillRect(surface, &tile, field[i][j] + 1);
    }
  }
}

void clear_field(void) {
  int i, j;
  for (i = 0; i < FIELD_HEIGHT; i++) {
    for (j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = -1;
    }
  }
}

