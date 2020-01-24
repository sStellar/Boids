/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <png.h>
#include <zlib.h>

//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

SDL_Surface* getPNG(std::string img_path) {
	bool success = true;
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* png_image = IMG_Load(img_path.c_str());
	if( png_image == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", img_path.c_str(), IMG_GetError() );
		success = false;
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( png_image, screenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", img_path.c_str(), SDL_GetError() );
			success = false;
		} else {
			return optimizedSurface;
		}
	}
}

void closeWindow(SDL_Window* window) {
	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

bool initWindow(const char* window_name, int open_time_s) {
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			//screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

			//Get window surface
      screenSurface = getPNG("/home/peter/Boids/sdl2/01_hello_SDL/preview.png");

			//Update the surface
			SDL_UpdateWindowSurface( window );

			closeWindow(window);
		}
	}
	return success;
}

int main()
{
	initWindow("Boids", 20);

	return 0;
}
