#include "header_ve.h"

/**
 * handling screen size for how the width and the height of the editor is to be rendered 
 * while users are using it .
 *
 * handling display size for the display may needs to fit screen size for better user
 * experience during usage .
 *
 * handling display position, having the display centered to the center of the screen
 * regardless of the screen size .
 **/

void display_sdl(void)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("Details",
				     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				     SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  assert(win);
  SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
  SDL_Texture *screen = SDL_CreateTexture(renderer, SDLPIXELFORMAT_RGB888,
					  SDL_TEXTUREACCESS_STREAMING,
					  SCREEN_WIDTH, SCREEN_HEIGHT);

  assert(screen);
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
  
