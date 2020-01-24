#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <png.h>
#include <zlib.h>

//Window to be rendered and its surface
SDL_Window* screenWindow = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* optimizedSurface = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;


SDL_Surface* loadSurfaceImage() {
  const std::string IMG_PATH = "/home/peter/Boids/sdl2/02_image/preview.png";
  //SDL Surface to be returned with img
  //Load Image
  SDL_Surface* loadedSurface = IMG_Load( IMG_PATH.c_str() );
  if( loadedSurface == NULL )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", IMG_PATH.c_str(), IMG_GetError() );
  } else {
    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, 0 );
    if( optimizedSurface == NULL ) {
      printf( "Unable to optimize image %s! SDL Error: %s\n", IMG_PATH.c_str(), SDL_GetError() );
    } else {
    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    return optimizedSurface;
    }

  }
}

bool initWindow()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Create window
    screenWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( screenWindow == NULL )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    } else {
      screenSurface = SDL_GetWindowSurface( screenWindow );
      //Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if( !( IMG_Init( imgFlags ) & imgFlags ) )
      {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
      }
      else
      {
        //Get window surface
        screenSurface = SDL_GetWindowSurface( screenWindow );
        SDL_UpdateWindowSurface(screenWindow);

        SDL_Delay( 2000 );
      }
    }
  }
  return success;
}

int main() {
  initWindow();
  if( !loadSurfaceImage() ) {
    printf( "Failed to load media!\n" );
  } else {
  SDL_BlitSurface( optimizedSurface, NULL, screenSurface, NULL );
  SDL_UpdateWindowSurface( screenWindow );
  }

  SDL_Quit();
  return 0;
}
