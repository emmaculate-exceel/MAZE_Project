#include "header_v2.h"

/**
 * setting up the viewport
 * positioning filename
 * positioning program name
 */

void text_editor(const char *filename) {
  size_t buffer_size = 1024; ///// initial buffer_size
  char *buffer = malloc(buffer_size * sizeof(char));

  if (buffer == NULL) {
    perror("Failed to allocate Memory");
    return;
  }

  memset(buffer, 0, buffer_size); /// initializing the buffer 
  char buffer[MAX_BUFFER_SIZE] = {0};
  int ch;
  size_t pos = 0;
  
  //// initializing ncurses
  initscr();
  cbreak(); /// disabling line buffering
  noecho(); /// Don't echo user input
  keypad(stdscr, TRUE); // Enable special input keys

  ///////// creating a window for the text editor
  WINDOW *editor_win = newwin(LINES - 1, COLS, 0, 0);
  box(editor_win, 0, 0);
  mvwprintw(editor_win, 0, 2, "VE Terminal Text Editor Version 0.02");
  wrefresh(editor_win);
  ////// editors field
  mvwprintw(editor_win, 1, 1, "Editing: %s", filename);
  wrefresh(editor_win);

  /////// Editors loop
  while (1) {
    mvwprintw(editor_win, 2, 1, "%s", buffer);
    wmove(editor_win, 2, pos + 1); /// move the cursor position
    wrefresh(editor_win);

    ch = wgetch(editor_win);

    if (ch == 27) { // if escape key is pressed close the program
      break;
    } else if (ch == 127 {// if backspace buttom is pressed erase the last input
	if (pos > 0) {
	  buffer[--pos] = '\0';
	}
      }else if (ch == KEY_LEFT) {
	if (pos > 0) pos--;
      }else if (ch == KEY_RIGHT){
	if (pos < strlen(buffer)) pos++;
      }else if (ch == 19) { //// control + S save to buffer
	FILE *file = fopen(filename, "w");
	if (file) {
	  fwrite(buffer, sizeof(char) , pos, file);
	  fclose(file);
	  mvwprintw(editor_win, LINES, 1, 1, "File saved. ");
	}else {
	  mvwprintw(editor_win, LINES, 1, 1, "Failed to save file. ");
	}
	wrefresh(editor_w);
      }else {
	///check the need for extending the buffer
	if (pos >= buffer_size - 1) {
	  buffer_size = realloc(buffer, buffer_size * sizeof(char));
	  if (buffer == NULL) {
	    perror("Failed to reallocate memory");
	    break; /// exiting the loop on memory failure
	  }
	}
	buffer[pos++] = ch;
	buffer[pos] = '\0'; /// terminating NULL
      }
    }

    endwin()/// close ncurses window


    FILE *file = fopen(filename, "w");
    if (file) {
      fwrite(buffer, sizeof(char), pos, file);
      fclose(file);

    }else {
      perror("File not saved");
    }

    printf("File saved successfully.\n");

    ////////// free allocated memory
    free(buffer);
}
