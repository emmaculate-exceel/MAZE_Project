#ifndef HEADER_VE_H
#define HEADER_VE_H
/**
 *  creating of standard header files
 *  creating macros
 *  creating variables
 *  creating aliases
 *  creating functions declarations
 **/

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

// variable declarations

extern int displayWidth;
extern int displayHeight;


#endif /* HEADER_VE_H */
