#include <malloc.h>
#include "SDL/SDL.h"
#include "field.h"

Field make_field(void) {
  Field field = (Field)malloc(sizeof(int) * FIELD_WIDTH * FIELD_HEIGHT);
  return field;
}

void destroy_field(Field field) {
  free(field);
}

int field_get(Field field, int x, int y) {
  return field[x + y * FIELD_WIDTH];
}

void field_set(Field field, int x, int y, int color) {
  field[x + y * FIELD_WIDTH] = color;
}

void draw_field(Field field, SDL_Surface * surface) {
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
      SDL_FillRect(surface, &tile, NULL_SHAPE(field_get(field, j, i)) ? COLOR_FIELD_BACKGROUND : field_get(field, j, i));
    }
  }
}

void clear_field(Field field) {
  int i, j;
  for (i = 0; i < FIELD_HEIGHT; i++) {
    for (j = 0; j < FIELD_WIDTH; j++) {
      field_set(field, j, i, SHAPE_NULL);
    }
  }
}

void clear_line(Field field, int line) {
  int current_line;
  int i;

  for (current_line = line; current_line > 0; current_line--) {
    for (i = 0; i < FIELD_WIDTH; i++) {
      field_set(field, i, current_line, field_get(field, i, current_line - 1));
    }
  }
}

int clear_lines(Field field) {
  int i, j;
  int line_full;
  int lines_cleared = 0;

  for (i = 0; i < FIELD_HEIGHT; i++) {
    line_full = 1;
    for (j = 0; j < FIELD_WIDTH; j++) {
      if (NULL_SHAPE(field_get(field, j, i))) {
        line_full = 0;
      }
    }

    if (line_full) {
      clear_line(field, i);
      lines_cleared++;
    }
  }

  return lines_cleared;
}

int game_over(Field field) {
  int i;

  for (i = 0; i < FIELD_WIDTH; i++) {
    if (! NULL_SHAPE(field_get(field, i, 0))) {
      return 1;
    }
  }

  return 0;
}

