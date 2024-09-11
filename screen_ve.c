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

int displayWidth;
int displayHeight;

void Fill_scrn(rect_size rect, u32 pixel_color, u32 *screen_pixels)
{
  for (int row = 0; row < rect.h; ++row)
    {
       for (int col = 0; col < rect.w; ++col)
	{
	  screen_pixels[(row + rect.y) *displayWidth + col + rect.x] = pixel_color;
	}
    }
    

void display_sdl(void)
{

  
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL : Unable to initialize SDL_Error: %s\n", SDL_GetError());

      return;
    }

  SDL_DisplayMode displayMode;
  if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
      printf("Unable to get Display! SDL_Error: %s\n", SDL_GetError());
      SDL_Quit();
      return;
  }

  displayWidth = displayMode.w;
  displayHeight = displayMode.h;
  SDL_Window *win = SDL_CreateWindow("Details",
				     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				     displayWidth, displayHeight, SDL_WINDOW_SHOWN);
  assert(win);
  
  SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
  SDL_Texture *screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
					  SDL_TEXTUREACCESS_STREAMING,
					  displayWidth, displayHeight);
  assert(screen);
  
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
  u32 *screen_pixels = (u32 *) calloc(displayWidth, displayHeight * sizeof(u32));   
  assert(screen_pixels);

  rect_size square = {0, 0, 30, 30};
  u32 pixel_color =  SDL_MapRGB(format, 0, 0, 255);
  Fill_scrn(square, pixel_color, screen_pixels);
  BOOL complete = FALSE;

  while (!complete)
    {

      SDL_Event event;
      while (SDL_PollEvent(&event)) {

	if (event.type == SDL_QUIT) {

	  complete = TRUE; // if the user closes the window close the program
	  //break;
	} else if (event.type != SDL_KEYDOWN) {
	    SDL_Keycode code = event.key.keysym.sym;

	    if (code == SDLK_ESCAPE) { // if esc key is pressed exit the wind program
	    complete = TRUE;
	    //break;
	  }
	}

	/**SDL_Keycode code = event.key.keysym.sym;

	switch (code)
	  {

	    case SDLK_ESCAPE:
	      complete = TRUE;
	        break;
	    default:
	        break;
	  }**/

      }
    

      for (int i = 0; i < displayWidth * displayHeight; i++)
	{
	  screen_pixels[i] = 0xFF000000;
	}
      SDL_UpdateTexture(screen, NULL, screen_pixels, displayWidth * sizeof(u32));
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, screen, NULL, NULL);
      SDL_RenderPresent(renderer);
      SDL_Delay(16);
    }

  /**for (int i = 0; i < displayWidth * displayHeight; i++)
    {
      screen_pixels[i] = 0xFF000000;
    }
  **/

  /**
  SDL_UpdateTexture(screen, NULL, screen_pixels, displayWidth * sizeof(u32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, screen, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);
  **/
  
  free(screen_pixels);
  SDL_DestroyTexture(screen);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
