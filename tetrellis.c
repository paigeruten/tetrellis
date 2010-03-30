#include "SDL/SDL.h"
#include "tetrellis.h"

void tetrellis(SDL_Surface * surface) {
  SDL_Event event;
  int quit = 0;

  clear_field();

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

    draw_field(surface);
    SDL_UpdateRect(surface, 0, 0, 640, 480);

    SDL_Delay(1);
  }
}



