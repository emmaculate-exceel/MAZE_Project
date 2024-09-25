#include "header_v2.h"

/**
 * main program
 * using the main for the
 */

int main(int argc, char *argv[]) {
   text_editor(const char *filename);
   
   if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    text_editor(argv[1]);
    return 0;
}
