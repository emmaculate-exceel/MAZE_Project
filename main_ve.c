#include "header_ve.h"

/**
 * main : the main programme for handling user text input,
 * text formatting including users input and output
 *
 *
 */

char buffer[MAX_BUFFER_SIZE] = "VE!";
int cursorX = 0, cursorY = 0;
int scrollOffset = 0;

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

void render_text(const char* text, SDL_Renderer* renderer){
  char* text_copy = strdup(text);
  char* line = strtok(text_copy, "\n");
  int y = -scrollOffset;

  while (line != NULL) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, line, textColor);
    if (textSurface) {
      SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
      if (textTexture) {
	SDL_Rect textRect = {0, y, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
      }

      SDL_FreeSurface(textSurface);
    }
    y += 20;
    line = strtok(NULL, "\n");
  }
  free(text_copy);
}

void render_cursor(SDL_Render* renderer, int x, int y) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black backgroud color
  SDL_RenderDrawLine(renderer, x, y, x, y + 20); //adjusting cursor as needed
}


void handle_input(SDL_Event* event) {
  if (event->type == SDL_TEXTINPUT) {
    strncat(buffer, event->text.text, sizof(buffer) - strlen(buffer) -1);
  }else if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_BACKSPACE:
	if (strlen(buffer) > 0) buffer [strlen(buffer) - 1] = '\0';//last char
	break;
      case SDLK_DELETE:
	////handle delete key
	break;
      case SDLK_UP:
	scrollOffset += 10;
	break;
      case SDLK_DOWN:
        scrollOffset -= 10;
	break;
      case SDLK_LEFT:
        ///handle cusor left movement
	break;
      case SDLK_RIGHT:
        //// handle cursor right movement
	break;
      case SDLK_s:
        save_to_file("output.txt", buffer);
        break;
    case SDLK_o:
      {
	char* loaded_text = load_from_file("input.txt");
	if (loaded_text) {
	  strncpy(buffer, loaded_text, sizeof(buffer) - 1);
	  buffer[sizeof(buffer) - 1] = '\0';//null termination string
	  free(loaded_text);
	}
      }
      break;
    }
  }
}

void update_text() {
  ///// update my text and cursor position

}


	    
/**  
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
**/

int main(int argc, char *argv[])
{
  
  display_sdl();
  
  return 0;
}
