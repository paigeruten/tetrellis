#ifndef _tetrellis_h
#define _tetrellis_h

#include "main.h"
#include "shapes.h"
#include "field.h"

typedef struct {
  int shape;
  int rot;
  int x;
  int y;
} Block;

void move_block(int dx, int dy);
void tetrellis(SDL_Surface * surface);

#endif

