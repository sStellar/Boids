#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

SDL_Window* main_window = NULL;
SDL_Surface* main_surface = NULL;
SDL_Surface* boid_bmp = NULL;
SDL_Event e;
SDL_Rect pos_rect;

// void placeBoidsRandom();
bool initSDLWindow();
bool loadBoidBMP();

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

class Boid {
  public:
    int x_pos = rand() % WIN_WIDTH;
    int y_pos = rand() % WIN_HEIGHT;
    int rotation;

    void placeBoid() {
      pos_rect.x = x_pos;
      pos_rect.y = y_pos;
      SDL_BlitSurface(boid_bmp, NULL, main_surface, &pos_rect); // Place the boid on pos spec in pos_rect
    }
// git test
    int boidDistanceSpec(Boid boid) {
      //sqrt( (x1 - x2)^2 + (y1 - y2)^2 )
      return hypot( (boid.x_pos - x_pos), (boid.y_pos - y_pos) ); //hypot(x,y) == sqrt(x^2 + y^2), used as cmnt above
    }

  private:
    int scan_radius = 100; // px
};

// void initBoids

int main() {
  srand(time(NULL)); // Random for positions of boids
  if (initSDLWindow()) {
    printf("Window created successfully\n");
  } else {
    printf("Window created unsuccessfully\n");
  }
  loadBoidBMP(); // Creates the boid bmp surface

  Boid boid1;
  Boid boid2;
  Boid boid3;
  Boid boid4;
  Boid boid5;


  Boid boid_list [6] = {boid1, boid2, boid3, boid4, boid5};
  for (int i = 0; i < 5; ++i) boid_list[i].placeBoid();

  printf("boid1 pos: %d, %d\n", boid1.x_pos, boid1.y_pos);
  printf("boid2 pos: %d, %d\n", boid2.x_pos, boid2.y_pos);

  printf("%d\n", boid1.boidDistanceSpec(boid2));

  SDL_UpdateWindowSurface(main_window);

  SDL_Delay(2000);
  return 0;
}
