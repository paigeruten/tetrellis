#include <stdlib.h>
#include "SDL/SDL.h"
#include "shapes.h"

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

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

void draw_shape(SDL_Surface * surface, int x, int y, int shape, int rot) {
  int tile_x, tile_y;

  SDL_Rect tile;
  tile.w = TILE_WIDTH;
  tile.h = TILE_HEIGHT;

  for (tile_x = 0; tile_x < SHAPE_WIDTH; tile_x++) {
    for (tile_y = 0; tile_y < SHAPE_HEIGHT; tile_y++) {
      if (shapes[shape][rot][tile_y][tile_x] == 1) {
        tile.x = x + tile_x * TILE_WIDTH;
        tile.y = y + tile_y * TILE_HEIGHT;
        SDL_FillRect(surface, &tile, shape * 5 + 5);
      }
    }
  }
}

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          break;

        case SDL_QUIT:
          quit = 1;
          break;

        default:
          break;
      }
    }
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

