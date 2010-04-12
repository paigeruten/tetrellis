#ifndef _tetrellis_h
#define _tetrellis_h

#include "main.h"
#include "shapes.h"
#include "field.h"
#include "block.h"
#include "next_shape.h"

#define INITIAL_SPEED 1000
#define INCREASE_SPEED_BY 50
#define LINES_NEEDED_FOR_NEXT_LEVEL 20

typedef struct {
  Block current_block;
  int next_shape;
  int last_tick;
  int speed;
  int lines_cleared;
  int level;
  int quit;
} Tetrellis;

void game(SDL_Surface * surface);

#endif

