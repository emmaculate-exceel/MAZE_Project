#include "header_v2.h"

/**
 * Setting up the viewport
 * Positioning filename
 * Positioning program name
 */

void text_editor(const char *filename) {
    size_t buffer_size = MAX_BUFFER_SIZE; 
    char *buffer = malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    memset(buffer, 0, buffer_size);
    int ch;
    size_t pos = 0;

    if (initscr() == NULL) {
        fprintf(stderr, "Failed to initialize ncurses\n");
        free(buffer);
        return;
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    ///// disabling flow control for the editor
    int old_flags = fcntl(fileno(stdin), F_GETFL, 0);
    fcntl(fileno(stdin), F_SETFL, old_flags & ~O_NONBLOCK);
    
    WINDOW *editor_win = newwin(LINES - 1, COLS, 0, 0);
    if (editor_win == NULL) {
        perror("Failed to create window");
        free(buffer);
        endwin();
        return;
    }
    
    box(editor_win, 0, 0);
    mvwprintw(editor_win, 0, 2, "VE Terminal Text Editor Version 0.02");
    wrefresh(editor_win);
    mvwprintw(editor_win, 1, 1, "Editing: %s", filename);
    wrefresh(editor_win);

    while (1) {
        mvwprintw(editor_win, 2, 1, "%s", buffer);
        wmove(editor_win, 2, pos + 1);
        wrefresh(editor_win);

        ch = wgetch(editor_win);

        if (ch == CTRL_X) { // Ctrl + X
            FILE *file = fopen(filename, "w");
            if (file) {
                fwrite(buffer, sizeof(char), pos, file);
                fclose(file);
                mvwprintw(editor_win, LINES - 1, 1, "File saved.   "); // Clear previous message
            } else {
                mvwprintw(editor_win, LINES - 1, 1, "Failed to save file.   ");
            }
            wrefresh(editor_win);
            continue; // Go back to the top of the loop
        } else if (ch == 27) { // Escape key
            break; // Exit the loop
        } else if (ch == 127) { // Backspace
            if (pos > 0) {
                buffer[--pos] = '\0';
            }
        } else if (ch == KEY_LEFT) {
            if (pos > 0) pos--;
        } else if (ch == KEY_RIGHT) {
            if (pos < strlen(buffer)) pos++;
        } else {
            // Extend buffer if necessary
            if (pos >= buffer_size - 1) {
                buffer_size *= 2; // Double the buffer size
                char *new_buffer = realloc(buffer, buffer_size * sizeof(char));
                if (new_buffer == NULL) {
                    free(buffer); // Free the old buffer
                    perror("Failed to reallocate memory");
                    endwin();
                    return;
                }
                buffer = new_buffer; // Update buffer pointer
            }
            if (pos < buffer_size - 1) {
                buffer[pos++] = ch;
                buffer[pos] = '\0'; // Null-terminate the string
            }
        }
    }

    endwin(); // Close ncurses window
    printf("Exited editor.\n");
    free(buffer); // Free allocated memory
}
