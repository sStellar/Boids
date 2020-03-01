#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

SDL_Window* main_window = NULL;
SDL_Surface* main_surface = NULL;
SDL_Surface* boid_bmp = NULL;
SDL_Renderer* renderer = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED);
SDL_Texture* texture = IMG_LoadTexture(renderer, "/home/peter/Boids/boid.bmp");
SDL_Rect texture_rect;


int main() {
  texture_rect.x = 0;
  texture_rect.y = 0;


  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
  SDL_RenderPresent(renderer);
}
