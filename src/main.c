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
	Libro libri[MAX_LIBRI] = {0};
	Cliente clienti[MAX_CLIENTI] = {0};
	Ordine ordini[MAX_ORDINI] = {0};

    int numeroClienti = 0;
    int numeroOrdini = 0;
    int numeroLibri = 0;

    // Creazione file binari per clienti

    FILE *clientiBinFile = fopen("clienti.bin", "rb");
    if (clientiBinFile == NULL) {
        // File non esistente, creiamolo.
        clientiBinFile = fopen("clienti.bin", "wb");
        if (clientiBinFile == NULL) {
            perror("Errore nell'apertura del file clienti.bin");
            return 1;
        }

        inizializzaClienti(clienti);
        numeroClienti = 20;

        for (int i = 0; i < numeroClienti; i++) {
            fwrite(clienti[i].idCliente, sizeof(clienti[i].idCliente), 1, clientiBinFile);
            fwrite(clienti[i].nome, sizeof(clienti[i].nome), 1, clientiBinFile);
            fwrite(clienti[i].cognome, sizeof(clienti[i].cognome), 1, clientiBinFile);
            fwrite(&clienti[i].numeroOrdini, sizeof(clienti[i].numeroOrdini), 1, clientiBinFile);
        }
        fclose(clientiBinFile);
        printf("File binario 'clienti.bin' creato con successo.\n");

    } 	else {
        fclose(clientiBinFile);
    }


    // Creazione file binari per libri

    printf("Creazione file binari per libri...\n");
    FILE *libriBinFile = fopen("libri.bin", "wb");
    if (libriBinFile == NULL) {
        perror("Errore nell'apertura del file libri.bin");
        return 1;
    }
    inizializzaLibri(libri);
    fwrite(libri, sizeof(Libro), 20, libriBinFile);
    fclose(libriBinFile);
    printf("File binario 'libri.bin' creato con successo.\n");

    // Creazione file binari per ordini

    printf("Creazione file binari per ordini...\n");
    FILE *ordiniBinFile = fopen("ordini.bin", "rb");
    if (ordiniBinFile == NULL) {
        // File non esistente, creiamolo.
        ordiniBinFile = fopen("ordini.bin", "wb");
        if (ordiniBinFile == NULL) {
            perror("Errore nell'apertura del file ordini.bin");
            return 1;
        }

        inizializzaOrdini(ordini);
        fwrite(ordini, sizeof(Ordine), MAX_ORDINI, ordiniBinFile);
        fclose(ordiniBinFile);
        printf("File binario 'ordini.bin' creato con successo.\n");

    } else {
        fclose(ordiniBinFile);
    }

    // Caricamento dei dati dai file
    printf("Caricamento dei clienti...\n");
    caricaClienti(clienti, &numeroClienti, MAX_CLIENTI);
    printf("Caricamento degli ordini...\n");
    caricaOrdini(ordini, &numeroOrdini, MAX_ORDINI);
    printf("Caricamento dei libri...\n");
    caricaLibri(libri, &numeroLibri);

    printf("Sto per chiamare gestioneMenu. \n");
    gestioneMenu(clienti, &numeroClienti, ordini, &numeroOrdini, libri, numeroLibri);

    // Salvataggio dei dati sui file prima di uscire
    if (salvaClienti(clienti, numeroClienti) == -1) {
        printf("Errore durante il salvataggio dei clienti.\n");
        return 1; // termina il programma con un codice d'errore
    }
    salvaOrdini(ordini, numeroOrdini);
    salvaLibri(libri, numeroLibri); 

    return 0;
}
