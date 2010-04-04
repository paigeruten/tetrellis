#include <stdlib.h>
#include <time.h>
#include "SDL/SDL.h"
#include "main.h"
#include "shapes.h"
#include "tetrellis.h"

void init_palette(SDL_Surface * surface) {
  SDL_Color colors[256];

  // shapes
  colors[COLOR_SHAPE_I] = (SDL_Color){ 255, 0, 0 };
  colors[COLOR_SHAPE_J] = (SDL_Color){ 255, 127, 0 };
  colors[COLOR_SHAPE_L] = (SDL_Color){ 0, 255, 0 };
  colors[COLOR_SHAPE_S] = (SDL_Color){ 0, 0, 255 };
  colors[COLOR_SHAPE_Z] = (SDL_Color){ 0, 255, 255 };
  colors[COLOR_SHAPE_T] = (SDL_Color){ 255, 255, 0 };
  colors[COLOR_SHAPE_O] = (SDL_Color){ 255, 0, 255 };

  colors[COLOR_BACKGROUND] = (SDL_Color){ 180, 180, 180 };
  colors[COLOR_FIELD_BACKGROUND] = (SDL_Color){ 100, 100, 100 };
  colors[COLOR_FIELD_BORDER] = (SDL_Color){ 0, 0, 0 };

  SDL_SetColors(surface, colors, 0, NUM_COLORS);
}

int main(int argc, char * argv[]) {
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);

  // make a screen
  SDL_Surface * screen;
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 8, SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, "Couldn't set %dx%dx8 video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
    exit(1);
  }
  SDL_FillRect(screen, NULL, COLOR_BACKGROUND);

  // init palette
  init_palette(screen);

  // seed randomizer
  srand(time(NULL));

  // to the game
  tetrellis(screen);

  return 0;
}
