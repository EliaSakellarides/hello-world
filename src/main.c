#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "ordine.h"
#include "libro.h"
#include "menu.h"
#include "ricerca.h"
#include "algoritmoOrdinamento.h"
#include "util.h"

int main() {
    Libro libri[MAX_LIBRI];
    Cliente clienti[MAX_CLIENTI];
    Ordine ordini[MAX_ORDINI];

    int numeroClienti = 20; //se sbaglio modifica di nuovo a 20
    int numeroOrdini = 0;
    int numeroLibri = 20;


    printf("Creazione file binari per clienti...\n");
    FILE *clientiBinFile = fopen("clienti.bin", "a+b");
    if (!clientiBinFile) {
        perror("Errore nell'apertura del file clienti.bin");
        return 1;
    }

    fseek(clientiBinFile, 0, SEEK_END);
    long size = ftell(clientiBinFile);
    fseek(clientiBinFile, 0, SEEK_SET);

    if (size == 0) {
        inizializzaClienti(clienti);
        numeroClienti = 20;

        int tempVersion = CLIENTI_FILE_VERSION;
        fwrite(&tempVersion, sizeof(int), 1, clientiBinFile);
        fwrite(&numeroClienti, sizeof(int), 1, clientiBinFile);

        for (int i = 0; i < numeroClienti; i++) {
            fwrite(&clienti[i], sizeof(Cliente), 1, clientiBinFile);
        }

        printf("File binario 'clienti.bin' creato con successo.\n");
    } else {
        int tempVersion;
        fread(&tempVersion, sizeof(int), 1, clientiBinFile);
        if (tempVersion != CLIENTI_FILE_VERSION) {
            printf("Versione attesa: %d, Versione trovata nel file: %d\n", CLIENTI_FILE_VERSION, tempVersion);
            printf("Versione del file non supportata.\n");
            fclose(clientiBinFile);
            return 1;
        }
        fread(&numeroClienti, sizeof(int), 1, clientiBinFile);  // Leggi il numero di clienti
        fread(clienti, sizeof(Cliente), numeroClienti, clientiBinFile);  // Ora leggi i dati dei clienti
    }
    fclose(clientiBinFile);



    // Gestione file binari per libri
    printf("Gestione file binari per libri...\n");
    FILE *libriBinFile = fopen("libri.bin", "a+b");
    if (!libriBinFile) {
        perror("Errore nell'apertura del file libri.bin");
        return 1;
    }

    fseek(libriBinFile, 0, SEEK_END);
    long libriSize = ftell(libriBinFile);
    fseek(libriBinFile, 0, SEEK_SET);

    if (libriSize == 0) {
        inizializzaLibri(libri);
        int tempVersion = LIBRI_FILE_VERSION; // Supponendo che tu abbia una definizione simile per LIBRI_FILE_VERSION
        fwrite(&tempVersion, sizeof(int), 1, libriBinFile);
        fwrite(libri, sizeof(Libro), 20, libriBinFile);
        printf("File binario 'libri.bin' creato con successo.\n");
    } else {
        int tempVersion;
        fread(&tempVersion, sizeof(int), 1, libriBinFile);
        if (tempVersion != LIBRI_FILE_VERSION) {
            printf("Versione attesa: %d, Versione trovata nel file: %d\n", LIBRI_FILE_VERSION, tempVersion);
            printf("Versione del file non supportata.\n");
            fclose(libriBinFile);
            return 1;
        }
        fread(libri, sizeof(Libro), 20, libriBinFile);
    }
    fclose(libriBinFile);



    // Creazione file binari per ordini
    printf("Creazione file binari per ordini...\n");
    FILE *ordiniBinFile = fopen("ordini.bin", "a+b");
    if (!ordiniBinFile) {
        perror("Errore nell'apertura del file ordini.bin");
        return 1;
    }

    fseek(ordiniBinFile, 0, SEEK_END);
    long ordiniSize = ftell(ordiniBinFile);
    fseek(ordiniBinFile, 0, SEEK_SET);
    if (ordiniSize == 0) {
        inizializzaOrdini(clienti, libri, ordini, numeroClienti, numeroLibri);
        numeroOrdini = MAX_ORDINI; // Aggiunto l'aggiornamento di numeroOrdini
        fwrite(ordini, sizeof(Ordine), numeroOrdini, ordiniBinFile);
        printf("File binario 'ordini.bin' creato con successo.\n");
    } else {
        fread(ordini, sizeof(Ordine), MAX_ORDINI, ordiniBinFile);
        // Aggiornare numeroOrdini qui se hai una logica simile a quella dei clienti
    }
    fclose(ordiniBinFile);






    printf("Sto per chiamare gestioneMenu. \n");
    gestioneMenu(clienti, &numeroClienti, ordini, &numeroOrdini, libri, numeroLibri);

    // Salvataggio dei dati sui file prima di uscire
    if (salvaClienti(clienti, numeroClienti) == -1) {
        printf("Errore durante il salvataggio dei clienti.\n");
        return 1;
    }
    salvaLibri(libri, numeroLibri);
    salvaOrdini(ordini, numeroOrdini);

    return 0;
}
