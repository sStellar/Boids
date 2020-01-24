/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	bool quit = false;
	SDL_Event e;

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
			screenSurface = SDL_GetWindowSurface( window );
			SDL_UpdateWindowSurface( window );
		}
	}

	while (true) {
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT) {
			break;
		} else if (e.type == SDL_KEYDOWN){
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0xFF, 0 ) );
					break;
				case SDLK_LEFT:
					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0xFF ) );
					break;
				case SDLK_RIGHT:
					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0, 0 ) );
					break;
				case SDLK_DOWN:
					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
					break;
				default:
					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0  ) );
					break;
			}
		}
		SDL_UpdateWindowSurface( window );
	}

	return 0;
}
