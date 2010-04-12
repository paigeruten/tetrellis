#include "SDL/SDL.h"
#include "next_shape.h"

void draw_next_shape(SDL_Surface * surface, int shape) {
  int i, j;

  SDL_Rect border;
  border.x = NEXT_SHAPE_X - NEXT_SHAPE_BORDER;
  border.y = NEXT_SHAPE_Y - NEXT_SHAPE_BORDER;
  border.w = NEXT_SHAPE_WIDTH * TILE_WIDTH + NEXT_SHAPE_BORDER * 2;
  border.h = NEXT_SHAPE_HEIGHT * TILE_HEIGHT + NEXT_SHAPE_BORDER * 2;

  SDL_Rect background;
  background = border;
  background.x += NEXT_SHAPE_BORDER;
  background.y += NEXT_SHAPE_BORDER;
  background.w -= NEXT_SHAPE_BORDER * 2;
  background.h -= NEXT_SHAPE_BORDER * 2;

  SDL_FillRect(surface, &border, COLOR_FIELD_BORDER);
  SDL_FillRect(surface, &background, COLOR_FIELD_BACKGROUND);

  draw_shape(surface,
             NEXT_SHAPE_X + (NEXT_SHAPE_WIDTH * TILE_WIDTH - real_shape_width(shape, 0) * TILE_WIDTH) / 2,
             NEXT_SHAPE_Y + (NEXT_SHAPE_HEIGHT - real_shape_height(shape, 0)) * TILE_HEIGHT / 2 - (SHAPE_HEIGHT - real_shape_height(shape, 0)) * TILE_HEIGHT,
             shape,
             0);
}

