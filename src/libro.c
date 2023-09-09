#include "libro.h"
#include <stdio.h>
#include <string.h>

#define FILE_LIBRI "libri.bin"




void inizializzaLibri(Libro libri[]) {
    char *titoli[] = {
        "Storia del Mondo", "Grammatica Italiana", "English Basics", "Matematica Applicata", "Introduzione alle Scienze",
        "Geografia Generale", "L'Arte del Rinascimento", "Musica Classica Europea", "Diritto e Cittadinanza", "Lo Sport e la Mente",
        "Storia Contemporanea", "Letteratura Italiana", "English for Business", "Algebra e Geometria", "Scienze della Terra",
        "Geografia Economica", "Arte Moderna", "Musica nel XX Secolo", "Etica e Società", "Sport e Medicina"
    };

    char *autori[] = {
        "Mario Rossi", "Lucia Bianchi", "John Smith", "Elena Verdi", "Franco Nero",
        "Anna Giallo", "Stefano Blu", "Laura Marrone", "Giuseppe Arancio", "Paola Viola",
        "Antonio Grigio", "Sofia Rosato", "Michael Brown", "Carla Verde", "Riccardo Giallo",
        "Bruno Bianco-nero", "Sara Arcobaleno", "Tommaso Tuono", "Chiara Nuvola", "Roberto Sole"
    };

    int anniPubblicazione[] = {
        2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
        2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019
    };

    char *isbn[] = {
        "ISBN001", "ISBN002", "ISBN003", "ISBN004", "ISBN005",
        "ISBN006", "ISBN007", "ISBN008", "ISBN009", "ISBN010",
        "ISBN011", "ISBN012", "ISBN013", "ISBN014", "ISBN015",
        "ISBN016", "ISBN017", "ISBN018", "ISBN019", "ISBN020"
    };

    char *scuola[20];

       // Inizializza "Scuola Primaria" per i primi 10 libri
       for (int i = 0; i < 10; i++) {
           scuola[i] = "Scuola Primaria";
       }

       // Inizializza "Scuola Secondaria I Grado" per i libri dall'11 al 15
       for (int i = 10; i < 15; i++) {
           scuola[i] = "Scuola Secondaria I Grado";
       }

       // Inizializza "Scuola Secondaria II Grado" per i libri dal 16 al 20
       for (int i = 15; i < 20; i++) {
           scuola[i] = "Scuola Secondaria II Grado";
       }

    for (int i = 0; i < 20; i++) {
           snprintf(libri[i].idLibro, sizeof(libri[i].idLibro), "L%03d", i+1);
           strncpy(libri[i].titolo, titoli[i], sizeof(libri[i].titolo) - 1);
           libri[i].titolo[sizeof(libri[i].titolo) - 1] = '\0';

           strncpy(libri[i].autore, autori[i], sizeof(libri[i].autore) - 1);
           libri[i].autore[sizeof(libri[i].autore) - 1] = '\0';

           libri[i].annoPubblicazione = anniPubblicazione[i];
           strncpy(libri[i].isbn, isbn[i], sizeof(libri[i].isbn) - 1);
           libri[i].isbn[sizeof(libri[i].isbn) - 1] = '\0';

           strncpy(libri[i].scuola, scuola[i], sizeof(libri[i].scuola) - 1);
           libri[i].scuola[sizeof(libri[i].scuola) - 1] = '\0';
       }
   }

void visualizzaLibri(Libro libri[], int numeroLibri) {
    if (numeroLibri == 0) {
        printf("Non ci sono libri disponibili.\n");
        return;
    }


        printf("Ecco la lista dei libri:\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("%-10s %-30s %-30s %-20s %-5s %-20s\n",
               "ID", "Titolo", "Autore", "ISBN", "Anno", "Scuola");
        printf("-------------------------------------------------------------------------------\n");
        for (int i = 0; i < numeroLibri; i++) {
            printf("%-10s %-30s %-30s %-20s %-5d %-20s\n",
                   libri[i].idLibro, libri[i].titolo, libri[i].autore,
                   libri[i].isbn, libri[i].annoPubblicazione, libri[i].scuola);
        }
        printf("-------------------------------------------------------------------------------\n");
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



Libro* trovaLibroPerIdOTitolo(Libro* libri, int numeroLibri, char* inputLibro) {
    for(int i = 0; i < numeroLibri; i++) {
        if (strcmp(libri[i].titolo, inputLibro) == 0 || strcmp(libri[i].idLibro, inputLibro) == 0) {
            // Trovato libro con il titolo o l'ID specificato
            return &libri[i];
        }
    }
    return NULL; // ritorna NULL se il libro non viene trovato
}



const Libro *ricercaLibroPerISBN(const Libro libri[], int numeroLibri, const char *isbn)
{
    for(int i = 0; i < numeroLibri; i++) {
        if(strcmp(libri[i].isbn, isbn) == 0) {
            return &libri[i];
        }
    }


    return NULL;  // Restituisci NULL se l'ISBN non viene trovato
}

