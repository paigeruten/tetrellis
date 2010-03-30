#ifndef _shapes_h
#define _shapes_h

#define NUM_SHAPES 7
#define NUM_ROTATIONS 4
#define SHAPE_WIDTH 4
#define SHAPE_HEIGHT 4

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

void draw_shape(SDL_Surface * surface, int x, int y, int shape, int rot);

#endif

