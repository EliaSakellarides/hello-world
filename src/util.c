#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pulisciBuffer() {
    int ch;
    // Discard characters until a newline or end of file is encountered
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void leggiRiga(char* buffer, int size) {
    if (buffer && size > 0) {
        if (fgets(buffer, size, stdin)) {
            char* newline = strchr(buffer, '\n');
            if (newline) {
                *newline = '\0';
            } else {
                pulisciBuffer();
            }
        }
    }
}
