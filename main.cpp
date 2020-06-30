#include <SDL2/SDL.h>
#include <stdio.h>

using namespace std;

// SCREEN DIMENTION CONSTANTS
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Globals
// NOTE: Not the best
//
struct SdlData {
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Surface *imageSurface;
};

/*
 * Initializes the SDL window and surface
 */
bool init(SdlData &sdlData) {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    sdlData.window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                      SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (sdlData.window == NULL) {
      success = false;
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      sdlData.screenSurface = SDL_GetWindowSurface(sdlData.window);
    }
  }

  return success;
}

/*
 * Loads a bmp image to the global surface
 */
bool loadMedia(SdlData &sdlData) {
  bool success = true;

  sdlData.imageSurface =
      SDL_LoadBMP("/Users/maxm/Development/SDL_Tutorial/hello_world.bmp");

  if (sdlData.imageSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n",
           "/Users/maxm/Development/SDL_Tutorial/hello_world.bmp",
           SDL_GetError());
    success = false;
  }

  return success;
}

void close(SdlData &sdlData) {
  // Deallocate surface
  SDL_FreeSurface(sdlData.imageSurface);
  sdlData.imageSurface = NULL;

  // Destroy window
  SDL_DestroyWindow(sdlData.window);
  sdlData.window = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {
  SdlData sdlData = {NULL, NULL, NULL};

  if (!init(sdlData)) {
    printf("Failed to initialize!\n");
  } else {
    if (!loadMedia(sdlData)) {
      printf("Failed to load media!\n");
    } else {
      SDL_BlitSurface(sdlData.imageSurface, NULL, sdlData.screenSurface, NULL);
    }
  }

  // Update the surface
  SDL_UpdateWindowSurface(sdlData.window);

  // Event loop
  // Simply waiting does not work on osx
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        quit = true;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        quit = true;
      }
    }
  }

  close(sdlData);

  return 0;
}
