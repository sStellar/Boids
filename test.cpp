#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int BMP_WIDTH = 24;
const int BMP_HEIGHT = 36;

const int NUM_OF_BOIDS = 5;
const int LOOP_DELAY = 100; // Delay after calculations in main loop (int in milliseconds)

SDL_Window* main_window = NULL;
SDL_Surface* main_surface = NULL;
SDL_Renderer* main_renderer = NULL;
SDL_Surface* boid_bmp = NULL;
SDL_Texture* boid_texture = NULL;
SDL_Event e;
SDL_Rect pos_rect;

// void placeBoidsRandom();
bool initSDLWindow();
bool loadBoidBMP();
void createIMGTexture();

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

void close() {
  //Free loaded image
  SDL_DestroyTexture(boid_texture);
  boid_texture = NULL;
  //Destroy window
  SDL_DestroyRenderer(main_renderer);
  SDL_DestroyWindow(main_window);
  main_window = NULL;
  main_renderer = NULL;
  //Quit SDL subsystems
  SDL_Quit();
}


class Boid {
  public:
    int x_pos = rand() % WIN_WIDTH;
    int y_pos = rand() % WIN_HEIGHT;
    int rotation = 0;

    void placeBoid() {
      pos_rect.x = x_pos;
      pos_rect.y = y_pos;
      pos_rect.w = BMP_WIDTH;
      pos_rect.h = BMP_HEIGHT;
      SDL_RenderCopyEx(main_renderer, boid_texture, NULL, &pos_rect, rotation, NULL, SDL_FLIP_NONE);
      // copy texture to renderer(renderer, texture, NULL = entire texture, texture px scale, rotation, NULL = rotate from center, flip)
    }

    int boidDistance(Boid boid) {
      //sqrt( (x1 - x2)^2 + (y1 - y2)^2 ) pythagoras sats
      return hypot( (boid.x_pos - x_pos), (boid.y_pos - y_pos) ); //hypot(x,y) == sqrt(x^2 + y^2)
    }

    bool boidCollision(int distance = 0) {
      // int distance = boidDistance(boid);
      if (distance < scan_radius) {
        return true;
      } else {
        return false;
      }
    }

    int boidRotation(Boid dist_boid) {
      // angle v = sin^-1(y/dist)
      // double asin(double x)
      //double rot = asin
      return 0;
    }

  private:
    int scan_radius = 100; // px
};

int main() {
  srand(time(NULL)); // Random for positions of boids
  if (initSDLWindow()) {
    printf("Window created successfully\n");
  } else {
    printf("Window created unsuccessfully! SDL Error: %s\n", SDL_GetError());
  }
  main_renderer = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderClear(main_renderer);

  // Load Boid BMP and make boid_texture have boid_bmp surface, free boid_bmp
  createIMGTexture();
  if (boid_texture == NULL) printf("Texture not loaded! SDL_Error: %s\n", SDL_GetError());

  Boid boid_list [NUM_OF_BOIDS+1];

  int boid_distance;
  bool running = true;

  while (running) { // == true
    SDL_RenderClear(main_renderer);

    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_ESCAPE) {
        break;
      }
    } // Quit loop

    for (int i = 0; i < NUM_OF_BOIDS; i++) {
      boid_list[i].placeBoid();
      printf("rot: %d, boid: %d\n", boid_list[i].rotation, i);
    } // Place boid loop

    for (int i = 0; i <= NUM_OF_BOIDS; i++) {
      for (int sub_i = 0; sub_i <= NUM_OF_BOIDS; sub_i++) {
        if (sub_i != i) {
          boid_distance = boid_list[i].boidDistance(boid_list[sub_i]);
          printf("distance: %d boid %d boid %d\n", boid_distance, i, sub_i);
          printf("col: %s\n", boid_list[i].boidCollision(boid_distance) ? "true" : "false");
          // printf("%s", x ? "true" : "false")
        }
      }
    } // Distance and collision loop

    SDL_RenderPresent(main_renderer);
    SDL_Delay(LOOP_DELAY);
  }
  close();
  return 0;
}
