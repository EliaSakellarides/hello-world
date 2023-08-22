#include "libro.h"
#include <stdio.h>
#include <string.h>

#define FILE_LIBRI "libri.bin"

void inizializzaLibri(Libro libri[]) {
    char *titoli[] = {
        "Storia Primaria", "Italiano Primaria", "Inglese Primaria", "Matematica Primaria", "Scienze Primaria",
        "Geografia Primaria", "Arte Primaria", "Musica Primaria", "Civica Primaria", "Sport Primaria",
        "Storia Secondaria", "Italiano Secondaria", "Inglese Secondaria", "Matematica Secondaria", "Scienze Secondaria",
        "Geografia Secondaria", "Arte Secondaria", "Musica Secondaria", "Civica Secondaria", "Sport Secondaria"
    };

    char *autori[] = {
        "Autore Storia P", "Autore Italiano P", "Autore Inglese P", "Autore Matematica P", "Autore Scienze P",
        "Autore Geografia P", "Autore Arte P", "Autore Musica P", "Autore Civica P", "Autore Sport P",
        "Autore Storia S", "Autore Italiano S", "Autore Inglese S", "Autore Matematica S", "Autore Scienze S",
        "Autore Geografia S", "Autore Arte S", "Autore Musica S", "Autore Civica S", "Autore Sport S"
    };

    int anniPubblicazione[] = {
        2000, 2005, 2010, 2015, 2020, 2002, 2007, 2012, 2017, 2004,
        2009, 2014, 2019, 2006, 2011, 2016, 2008, 2013, 2018, 2003
    };

    char *isbn[] = {
        "ISBN001", "ISBN002", "ISBN003", "ISBN004", "ISBN005",
        "ISBN006", "ISBN007", "ISBN008", "ISBN009", "ISBN010",
        "ISBN011", "ISBN012", "ISBN013", "ISBN014", "ISBN015",
        "ISBN016", "ISBN017", "ISBN018", "ISBN019", "ISBN020"
    };

    char *scuole[] = {
        "Scuola Primaria", "Scuola Primaria", "Scuola Primaria", "Scuola Primaria", "Scuola Primaria",
        "Scuola Primaria", "Scuola Primaria", "Scuola Primaria", "Scuola Primaria", "Scuola Primaria",
        "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria",
        "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria", "Scuola Secondaria"
    };

    for (int i = 0; i < 20; i++) {
           snprintf(libri[i].idLibro, sizeof(libri[i].idLibro), "L%03d", i+1);
           strncpy(libri[i].titolo, titoli[i], sizeof(libri[i].titolo) - 1);
           libri[i].titolo[sizeof(libri[i].titolo) - 1] = '\0';  // Termination for safety

           strncpy(libri[i].autore, autori[i], sizeof(libri[i].autore) - 1);
           libri[i].autore[sizeof(libri[i].autore) - 1] = '\0';  // Termination for safety

           libri[i].annoPubblicazione = anniPubblicazione[i];
           strncpy(libri[i].isbn, isbn[i], sizeof(libri[i].isbn) - 1);
           libri[i].isbn[sizeof(libri[i].isbn) - 1] = '\0';  // Termination for safety

           strncpy(libri[i].scuola, scuole[i], sizeof(libri[i].scuola) - 1);
           libri[i].scuola[sizeof(libri[i].scuola) - 1] = '\0';  // Termination for safety
       }
   }



void caricaLibri(Libro libri[], int *numeroLibri) {
    FILE *file = fopen(FILE_LIBRI, "rb");
    if (!file) {
        printf("Errore nell'apertura del file dei libri. \n");
        *numeroLibri = 0;
        return;
    }

    *numeroLibri = fread(libri, sizeof(Libro), MAX_LIBRI, file);
    fclose(file);
}

void salvaLibri(const Libro libri[], int numeroLibri) {
    FILE *file = fopen(FILE_LIBRI, "wb");
    if (!file) {
        printf("Errore nell'apertura del file dei libri. \n");
        return; 
    }

    fwrite(libri, sizeof(Libro), numeroLibri, file);
    fclose(file);
}

void aggiungiLibro(Libro libri[], int *numeroLibri, const Libro *nuovoLibro) {
    if (*numeroLibri >= MAX_LIBRI) {
        printf("Numero massimo di libri raggiunto.\n");
        return;
    }

    libri[*numeroLibri] = *nuovoLibro;
    (*numeroLibri)++;
    salvaLibri(libri, *numeroLibri);
}

const Libro *ricercaLibroPerISBN(const Libro libri[], int numeroLibri, const char *isbn) {
    for (int i = 0; i < numeroLibri; i++) {
        if (strcmp(libri[i].isbn, isbn) == 0) {
            return &libri[i];
        }
    }  
    return NULL;
}
