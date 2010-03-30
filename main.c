#include <stdlib.h>
#include "SDL/SDL.h"
#include "shapes.h"
#include "tetrellis.h"

void putpixel(SDL_Surface * surface, int x, int y, Uint32 pixel) {
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
  case 1:
    *p = pixel;
    break;

  case 2:
    *(Uint16 *)p = pixel;
    break;

  case 3:
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;

  case 4:
    *(Uint32 *)p = pixel;
    break;

  default:
    break;
  }
}

int main(int argc, char * argv[]) {
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);

  // make a screen
  SDL_Surface * screen;
  screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n", SDL_GetError());
    exit(1);
  }

  // to the game
  tetrellis(screen);

  return 0;
}
