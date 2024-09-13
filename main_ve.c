#include "header_ve.h"

/**
 * main : the main programme for handling user text input,
 * text formatting including users input and output
 *
 *
 */


void render_text(const char* text, SDL_Renderer* renderer, SDL_Texture* screen_texture){
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
  if (!textSurface) {
    printf("Failed to enable surface: %s\n", TTF_GetError());
    return;
  }

  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (!textTexture) {
    printf("Failed to enable texture: %s\n", SDL_GetError());
    SDL_FreeSurface(textSurface);
    return;
  }
  SDL_RenderCopy(renderer, textTexture, NULL, NULL);
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}


int main(int argc, char *argv[])
{
  
  display_sdl();
  
  return 0;
}
