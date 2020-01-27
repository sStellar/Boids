#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Event event;

void init_SDL() {
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    } else {
      //Get window surface
      surface = SDL_GetWindowSurface( window );
      SDL_UpdateWindowSurface( window );
    }
  }
}


int main() {
  int quit = 1;
  int red = 5;
  int blue = 5

  init_SDL();
  SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xff, 0xff, 0xff) );
  SDL_UpdateWindowSurface( window );


  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      quit = 0;
      break;
    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          if (red < 254) {
            ++red;
          }
          break;
        case SDLK_DOWN:
          if (red > 1) {
            --red;
          }
          break;
      }
    }
    printf("red: %d", red);
    printf("key: %d", event.key.keysym.key);

    SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, red, 0, 0  ) );
    SDL_UpdateWindowSurface(window);
  }
  return 0;
}
