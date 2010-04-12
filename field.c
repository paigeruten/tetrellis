#include "SDL/SDL.h"
#include "field.h"

int field[FIELD_HEIGHT][FIELD_WIDTH];

int field_get(int x, int y) {
  return field[y][x];
}

void field_set(int x, int y, int color) {
  field[y][x] = color;
}

void draw_field(SDL_Surface * surface) {
  int i, j;
  SDL_Rect tile;
  SDL_Rect border;

  border.x = FIELD_X - 2;
  border.y = FIELD_Y - 2;
  border.w = FIELD_WIDTH * TILE_WIDTH + 4;
  border.h = FIELD_HEIGHT * TILE_HEIGHT + 4;

  SDL_FillRect(surface, &border, COLOR_FIELD_BORDER);

  tile.w = TILE_WIDTH;
  tile.h = TILE_HEIGHT;

  for (i = 0; i < FIELD_HEIGHT; i++) {
    for (j = 0; j < FIELD_WIDTH; j++) {
      tile.x = FIELD_X + j * TILE_WIDTH;
      tile.y = FIELD_Y + i * TILE_HEIGHT;
      SDL_FillRect(surface, &tile, NULL_SHAPE(field[i][j]) ? COLOR_FIELD_BACKGROUND : field[i][j]);
    }
  }
}

void clear_field(void) {
  int i, j;
  for (i = 0; i < FIELD_HEIGHT; i++) {
    for (j = 0; j < FIELD_WIDTH; j++) {
      field[i][j] = SHAPE_NULL;
    }
  }
}

void clear_line(int line) {
  int current_line;
  int i;

  for (current_line = line; current_line > 0; current_line--) {
    for (i = 0; i < FIELD_WIDTH; i++) {
      field[current_line][i] = field[current_line - 1][i];
    }
  }
}

int clear_lines(void) {
  int i, j;
  int line_full;
  int lines_cleared = 0;

  for (i = 0; i < FIELD_HEIGHT; i++) {
    line_full = 1;
    for (j = 0; j < FIELD_WIDTH; j++) {
      if (NULL_SHAPE(field[i][j])) {
        line_full = 0;
      }
    }

    if (line_full) {
      clear_line(i);
      lines_cleared++;
    }
  }

  return lines_cleared;
}

int game_over(void) {
  int i;

  for (i = 0; i < FIELD_WIDTH; i++) {
    if (! NULL_SHAPE(field[0][i])) {
      return 1;
    }
  }

  return 0;
}

