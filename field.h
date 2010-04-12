#ifndef _field_h
#define _field_h

#include "main.h"
#include "shapes.h"

#define FIELD_WIDTH 14
#define FIELD_HEIGHT 20

#define FIELD_X ((SCREEN_WIDTH - FIELD_WIDTH * TILE_WIDTH) / 2)
#define FIELD_Y ((SCREEN_HEIGHT - FIELD_HEIGHT * TILE_HEIGHT) / 2)

int field[FIELD_HEIGHT][FIELD_WIDTH];

int field_get(int x, int y);
void field_set(int x, int y, int color);
void draw_field(SDL_Surface * surface);
void clear_field(void);
void clear_line(int line);
int clear_lines(void);
int game_over(void);

#endif

