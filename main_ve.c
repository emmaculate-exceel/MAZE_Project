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

/**void render_text(const char* text, SDL_Renderer* renderer){
  char* text_copy = strdup(text);
  char* line = strtok(text_copy, "\n");
  int y = -scrollOffset;
  int windowWidth = displayWidth; // using window to define width

  while (line != NULL) {
    char* lineStart = line;
    char* spacePos;
    int lineWidth = 0;

    while (line != NULL && lineWidth < windowWidth) {
      
      SDL_Surface* textSurface = TTF_RenderText_Solid(font, line, textColor);
      if (textSurface) {
	lineWidth = textSurface->w;
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture) {
	  SDL_Rect textRect = {0, y, textSurface->w, textSurface->h};
	  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	  SDL_DestroyTexture(textTexture);
        }

      SDL_FreeSurface(textSurface);

      if (lineWidth > windowWidth) {
	spacePos = strrchr(lineStart, ' ');
	if (spacePos == NULL) {
	  spacePos = lineStart + strlen(lineStart);//take all line if no space(s)
	}
	*spacePos = '\0'; // End the line at space
      }else {
	spacePos = lineStart + strlen(lineStart); // Move to the end of line
      }
      
      lineStart = spacePos + 1; // move to the next line
      }
      y += 20; //adjust the height 
    }
    line = strtok(NULL, "\n");
  }
  free(text_copy);
  }**/
void render_text(const char* text, SDL_Renderer* renderer) {
    char* text_copy = strdup(text);
    char* line = strtok(text_copy, "\n");
    int y = -scrollOffset;
    int windowWidth = displayWidth;// wrap text using the window

    while (line != NULL) {
        char* lineStart = line;
        int lineWidth = 0;

        while (lineStart) {
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, lineStart, textColor);
            if (textSurface) {
                lineWidth = textSurface->w;

                if (lineWidth > windowWidth) {
                    // Line is too wide, break it at the last space
                    char* spacePos = strrchr(lineStart, ' ');
                    if (spacePos != NULL) {
                        *spacePos = '\0'; // End the line at space
                        // Render the current line
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture) {
                            SDL_Rect textRect = {0, y, textSurface->w, textSurface->h};
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        SDL_FreeSurface(textSurface);
                        
                        // Move to the next part of the line
                        lineStart = spacePos + 1; // Move past the space
                        y += 20; // Move down for the next line
                    } else {
                        // No spaces, just render the rest
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture) {
                            SDL_Rect textRect = {0, y, textSurface->w, textSurface->h};
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        SDL_FreeSurface(textSurface);
                        break; // No more line breaks possible
                    }
                } else {
                    // Line fits within the width
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    if (textTexture) {
                        SDL_Rect textRect = {0, y, textSurface->w, textSurface->h};
                        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                        SDL_DestroyTexture(textTexture);
                    }
                    SDL_FreeSurface(textSurface);
                    break; // Move to the next line
                }
            } else {
                // Surface creation failed, handle this error
                fprintf(stderr, "Failed to create surface: %s\n", TTF_GetError());
                break; // Exit the loop
            }
        }
        y += 20; // Move down for the next line
        line = strtok(NULL, "\n");
    }
    free(text_copy);
}


void render_cursor(SDL_Renderer* renderer, int x, int y) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //color black
  SDL_Rect cursorRect = {x, y, 2, 20}; /// 2 pixel wide and 20 pixel tall
  SDL_RenderFillRect(renderer, &cursorRect);
  SDL_RenderDrawLine(renderer, x, y, x, y + 20); //adjusting cursor as needed
}

void handle_input(SDL_Event* event) {
    if (event->type == SDL_TEXTINPUT) {
        size_t len = strlen(buffer);
        size_t text_len = strlen(event->text.text);

        if (len + text_len < MAX_BUFFER_SIZE - 1) { // -1 for null terminator
            memmove(buffer + cursorX + text_len, buffer + cursorX, len - cursorX + 1);
            memcpy(buffer + cursorX, event->text.text, text_len);
            cursorX += text_len;
            buffer[MAX_BUFFER_SIZE - 1] = '\0'; // Ensure null termination
        }
    } else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_BACKSPACE:
                if (cursorX > 0) {
                    memmove(buffer + cursorX - 1, buffer + cursorX, strlen(buffer) - cursorX + 1);
                    cursorX--;
                }
                break;
            case SDLK_DELETE:
                if (cursorX < strlen(buffer)) {
                    memmove(buffer + cursorX, buffer + cursorX + 1, strlen(buffer) - cursorX);
                }
                break;
            case SDLK_LEFT:
                if (cursorX > 0) cursorX--;
                break;
            case SDLK_RIGHT:
                if (cursorX < strlen(buffer)) cursorX++;
                break;
            case SDLK_UP:
                scrollOffset += 10;  // Handle scrolling
                break;
            case SDLK_DOWN:
                scrollOffset -= 10;  // Handle scrolling
                break;
            case SDLK_s:
                save_to_file("output.txt", buffer);
                break;
            case SDLK_o:
                {
                    char* loaded_text = load_from_file("input.txt");
                    if (loaded_text) {
                        strncpy(buffer, loaded_text, sizeof(buffer) - 1);
                        buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
                        free(loaded_text);
                    }
                }
                break;
            default:
                break;
        }
    }
}


int main(int argc, char *argv[])
{
  
  display_sdl();
  
  return 0;
}
