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


// Global variable definitions
SDL_Color textColor = {255, 255, 255, 255}; // White text color
TTF_Font* font = NULL;
int displayWidth;
int displayHeight;

void display_sdl(const char* filename) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL: Unable to initialize SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (TTF_Init() == -1) {
        printf("Could not initialize font: SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        printf("Unable to get Display: SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    displayWidth = displayMode.w;
    displayHeight = displayMode.h;
    SDL_Window *win = SDL_CreateWindow("VE Terminal Text Editor",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       displayWidth, displayHeight, SDL_WINDOW_SHOWN);

    if (!win) {
        printf("Failed to initialize window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer failed to initialize: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return;
    }
    /// font type for the input text 
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return;
    }
   
    SDL_Color textColor = {255, 255, 255, 255}; // white text color 
    BOOL complete = FALSE;
    BOOL up = FALSE;
    BOOL down = FALSE;
    BOOL left = FALSE;
    BOOL right = FALSE;

    while (!complete) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
	  handle_input(&event, filename);
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                complete = TRUE;
            }
        }

        // Clear the renderer with a white background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render text and cursor
        render_text(buffer, renderer);
        render_cursor(renderer, cursorX, cursorY);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    /// clean up's 
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}
