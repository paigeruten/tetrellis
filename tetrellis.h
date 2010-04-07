#ifndef _tetrellis_h
#define _tetrellis_h

#include "main.h"
#include "shapes.h"
#include "field.h"

#define INITIAL_SPEED 1000
#define INCREASE_SPEED_BY 50
#define LINES_NEEDED_FOR_NEXT_LEVEL 20

#define NEXT_SHAPE_X (FIELD_X + FIELD_WIDTH * TILE_WIDTH + TILE_WIDTH)
#define NEXT_SHAPE_Y (FIELD_Y)
#define NEXT_SHAPE_WIDTH (SHAPE_WIDTH + 1)
#define NEXT_SHAPE_HEIGHT (SHAPE_HEIGHT + 1)
#define NEXT_SHAPE_BORDER 2

typedef struct {
  int shape;
  int rot;
  int x;
  int y;
} Block;

int collision(int shape, int rot, int x, int y);
void freeze_block(void);
void clear_line(int line);
int clear_lines(void);
int game_over(void);
void draw_next_shape(SDL_Surface * surface);
int move_block(int dx, int dy);
void rotate_block(void);
void drop_block(void);
void tetrellis(SDL_Surface * surface);

#endif

