#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int BMP_WIDTH = 24;
const int BMP_HEIGHT = 36;

SDL_Window* main_window = NULL;
SDL_Surface* main_surface = NULL;
SDL_Surface* boid_bmp = NULL;
SDL_Renderer* main_renderer;
SDL_Texture* boid_texture;
SDL_Rect dst_rect;

bool initSDLWindow() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
  } else {
    //Create window
		main_window = SDL_CreateWindow("Boids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN );
		if (main_window == NULL) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
    } else {
      main_surface = SDL_GetWindowSurface(main_window);
      SDL_FillRect(main_surface, NULL, SDL_MapRGB(main_surface->format,0,0,0)); // Fill the surface with just black
      SDL_UpdateWindowSurface(main_window);
    }
  }
  return success;
}

bool loadBoidBMP() {
	//Loading success flag
	bool success = true;
	//Load splash image
	boid_bmp = SDL_LoadBMP("/home/peter/Boids/boid.bmp");
	if(boid_bmp == NULL) {
		printf( "Unable to load boid.bmp! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void createIMGTexture() {
  // Create boid_texture for boids from boid bmp
  loadBoidBMP();
  boid_texture = SDL_CreateTextureFromSurface(main_renderer, boid_bmp);
  SDL_FreeSurface(boid_bmp);
}

int main() {
  initSDLWindow();

  main_renderer = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED);
  if (main_renderer == NULL) {
    printf( "Renderer not loaded! SDL_Error: %s\n", SDL_GetError() );
    return 0;
  }

  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.w = BMP_WIDTH;
  dst_rect.h = BMP_HEIGHT;

  createIMGTexture();
  // boid_texture = IMG_LoadTexture(main_renderer, "/home/peter/Boids/boid.bmp");
  if (boid_texture == NULL) {
    printf( "Texture not loaded! SDL_Error: %s\n", SDL_GetError() );
    return 0;
  }

  SDL_RenderClear(main_renderer);
  SDL_RenderCopy(main_renderer, boid_texture, NULL, &dst_rect);
  SDL_RenderPresent(main_renderer);

  SDL_Delay(2000);
  return 0;
}
