#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void text_editor(const char *filename) {
    char buffer[MAX_BUFFER_SIZE] = {0};
    int ch;
    size_t pos = 0;

    // Initialize ncurses
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Don't echo user input
    keypad(stdscr, TRUE); // Enable special keys

    // Create a window for the editor
    WINDOW *editor_win = newwin(LINES - 1, COLS, 0, 0);
    box(editor_win, 0, 0);
    mvwprintw(editor_win, 0, 2, " Simple Text Editor ");
    wrefresh(editor_win);

    mvwprintw(editor_win, 1, 1, "Editing file: %s", filename);
    wrefresh(editor_win);

    // Main editing loop
    while (1) {
        mvwprintw(editor_win, 2, 1, "%s", buffer);
        wmove(editor_win, 2, pos + 1); // Move cursor to position
        wrefresh(editor_win);

        ch = wgetch(editor_win);

        if (ch == 27) { // Escape key to exit
            break;
        } else if (ch == 127) { // Backspace
            if (pos > 0) {
                buffer[--pos] = '\0';
            }
        } else if (ch == KEY_LEFT) {
            if (pos > 0) pos--;
        } else if (ch == KEY_RIGHT) {
            if (pos < strlen(buffer)) pos++;
        } else {
            if (pos < MAX_BUFFER_SIZE - 1) {
                buffer[pos++] = ch;
                buffer[pos] = '\0'; // Null-terminate the string
            }
        }
    }

    // End ncurses mode
    endwin();

    // Save the buffer back to the file
    FILE *file = fopen(filename, "w");
    if (file) {
        fwrite(buffer, sizeof(char), pos, file);
        fclose(file);
    } else {
        perror("Failed to save file");
    }

    printf("File saved. Exiting...\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    text_editor(argv[1]);
    return 0;
}
