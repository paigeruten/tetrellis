#include <stdlib.h>
#include <time.h>
#include "SDL/SDL.h"
#include "main.h"
#include "shapes.h"
#include "tetrellis.h"

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

  // seed randomizer
  srand(time(NULL));

  // to the game
  tetrellis(screen);

  return 0;
}
