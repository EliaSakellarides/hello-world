// util.c
#include "util.h"      // Includi il file header per le funzioni di utilità
#include <stdio.h>     // Includi il file header standard per l'input/output
#include <stdlib.h>    // Includi il file header standard per le funzioni di allocazione
#include <string.h>

void pulisciBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void leggiRiga(char* buffer, int size) {

    if (buffer && size > 0) {
        if (fgets(buffer, size, stdin)) {
            // Rimuovere il newline alla fine, se presente
            char* newline = strchr(buffer, '\n');
            if (newline) {
                *newline = '\0';
            }
        }
    }
}
