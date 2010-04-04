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

int collision(int shape, int rot, int x, int y);
void freeze_block(void);
int move_block(int dx, int dy);
void rotate_block(void);
void drop_block(void);
void tetrellis(SDL_Surface * surface);

#endif

