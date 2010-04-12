#ifndef _field_h
#define _field_h

#include "main.h"
#include "shapes.h"

#define FIELD_WIDTH 14
#define FIELD_HEIGHT 20

#define FIELD_X ((SCREEN_WIDTH - FIELD_WIDTH * TILE_WIDTH) / 2)
#define FIELD_Y ((SCREEN_HEIGHT - FIELD_HEIGHT * TILE_HEIGHT) / 2)

typedef int* Field;

Field make_field(void);
void destroy_field(Field field);
int field_get(Field field, int x, int y);
void field_set(Field field, int x, int y, int color);
void draw_field(Field field, SDL_Surface * surface);
void clear_field(Field field);
void clear_line(Field field, int line);
int clear_lines(Field field);
int game_over(Field field);

#endif

