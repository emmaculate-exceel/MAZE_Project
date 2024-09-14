#ifndef HEADER_VE_H
#define HEADER_VE_H

/**
 *  creating of standard header files
 *  creating macros
 *  creating variables
 *  creating aliases
 *  creating functions declarations
 **/

#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <assert.h>

// macros

#define BOOL int
#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 1027
#define SCREEN_HEIGHT 776
#define MAX_BUFFER_SIZE 1024

// aliases

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 s32;
typedef Sint64 s64;
typedef struct {
  int x;
  int y;
  int h;
  int w;
}rect_size;

// Functions

void display_sdl(void);
void Fill_scrn(rect_size rect, u32 pixel_color, u32 *screen_pixels);
void render_text(const char* text, SDL_Renderer* renderer);
void save_to_file(const char* filename, const char* text);
char* load_from_file(const char* filename);
void handle_input(SDL_Event* event);
void update_text(void);
void render_cursor(SDL_Renderer* renderer, int x, int y);

// variable declarations

extern int displayWidth;
extern int displayHeight;
extern TTF_Font* font;
extern SDL_Color textColor;

#endif /* HEADER_VE_H */
