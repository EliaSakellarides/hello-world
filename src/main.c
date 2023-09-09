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
    int numeroLibri = 0;

    printf("Creazione file binari per clienti...\n");
    FILE *clientiBinFile = fopen("clienti.bin", "a+b");
    if (!clientiBinFile) {
        perror("Errore nell'apertura del file clienti.bin");
        return 1;
    }

    fseek(clientiBinFile, 0, SEEK_END);
    long size = ftell(clientiBinFile);
    fseek(clientiBinFile, 0, SEEK_SET);    if (size == 0) {
        inizializzaClienti(clienti);
        numeroClienti = MAX_CLIENTI;

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
    }
    fclose(clientiBinFile);


    // Creazione o caricamento file binari per libri
    printf("Gestione file binari per libri...\n");
    FILE *libriBinFile = fopen("libri.bin", "a+b");
    if (libriBinFile == NULL) {
        perror("Errore nell'apertura del file libri.bin");
        return 1;
    }

    fseek(libriBinFile, 0, SEEK_END);
    long libriSize = ftell(libriBinFile);
    fseek(libriBinFile, 0, SEEK_SET);
    if (libriSize == 0) {
        inizializzaLibri(libri);
        fwrite(libri, sizeof(Libro), 20, libriBinFile);
        printf("File binario 'libri.bin' creato con successo.\n");
    } else {
        // Se necessario, carica i dati dal file
        fread(libri, sizeof(Libro), 20, libriBinFile);
    }
    fclose(libriBinFile);


    // Creazione file binari per ordini
    printf("Creazione file binari per ordini...\n");
    FILE *ordiniBinFile = fopen("ordini.bin", "rb");
    if (ordiniBinFile == NULL) {
        ordiniBinFile = fopen("ordini.bin", "wb");
        if (ordiniBinFile == NULL) {
            perror("Errore nell'apertura del file ordini.bin");
            return 1;
        }

        inizializzaOrdini(clienti, libri, ordini, numeroClienti, numeroLibri);
        size_t result = fwrite(ordini, sizeof(Ordine), MAX_ORDINI, ordiniBinFile);
        if (result != MAX_ORDINI) {
            perror("Errore durante la scrittura degli ordini");
        }
        printf("File binario 'ordini.bin' creato con successo.\n");
    }
    fclose(ordiniBinFile);


    // Caricamento dei dati dai file
    printf("Caricamento dei clienti...\n");
    caricaClienti(clienti, &numeroClienti);

    printf("Caricamento dei libri...\n");
    caricaLibri(libri, &numeroLibri);

    printf("Caricamento degli ordini...\n");
    caricaOrdini(ordini, &numeroOrdini, MAX_ORDINI);





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
