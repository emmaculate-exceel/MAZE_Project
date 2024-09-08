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
  SDL_Texture *screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
					  SDL_TEXTUREACCESS_STREAMING,
					  SCREEN_WIDTH, SCREEN_HEIGHT);
  assert(screen);
  
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
  u32 *screen_pixels = (u32 *) calloc(SCREEN_WIDTH, SCREEN_HEIGHT * sizeof(u32));   
  assert(screen_pixels);

  for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
      screen_pixels[i] = 0xFF000000;
    }

  SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, screen, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);

  free(screen_pixels);
  SDL_DestroyTexture(screen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
