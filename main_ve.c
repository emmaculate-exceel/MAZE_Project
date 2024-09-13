#include "header_ve.h"

/**
 * main : the main programme for handling user text input,
 * text formatting including users input and output
 *
 *
 */

void save_to_file(const char* filename, const char* text) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(text, sizeof(char), strlen(text), file);
    fclose(file);
}

char* load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        return NULL;
    }

    char* buffer = malloc(MAX_BUFFER_SIZE);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    size_t size = fread(buffer, sizeof(char), MAX_BUFFER_SIZE - 1, file);
    if (size == 0) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0'; // Null-terminate the string
    fclose(file);
    return buffer;
}

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
