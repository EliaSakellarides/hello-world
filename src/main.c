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

    int numeroClienti = 0;
    int numeroOrdini = 0;
    int numeroLibri = 0;

    // Creazione file binari per clienti e libri
    printf("Creazione file binari per clienti...\n");
    FILE *clientiBinFile = fopen("clienti.bin", "wb");
    if (clientiBinFile == NULL) {
        perror("Errore nell'apertura del file clienti.bin");
        return 1;
    }
    fwrite(clienti, sizeof(Cliente), 20, clientiBinFile);
    fclose(clientiBinFile);
    printf("File binario 'clienti.bin' creato con successo.\n");

    printf("Creazione file binari per libri...\n");
    FILE *libriBinFile = fopen("libri.bin", "wb");
    if (libriBinFile == NULL) {
        perror("Errore nell'apertura del file libri.bin");
        return 1;
    }
    fwrite(libri, sizeof(Libro), 20, libriBinFile);
    fclose(libriBinFile);
    printf("File binario 'libri.bin' creato con successo.\n");

    // Caricamento dei dati dai file
    printf("Caricamento dei clienti...\n");
    caricaClienti(clienti, &numeroClienti, MAX_CLIENTI);
    printf("Caricamento degli ordini...\n");
    caricaOrdini(ordini, &numeroOrdini, MAX_ORDINI);
    printf("Caricamento dei libri...\n");
    caricaLibri(libri, &numeroLibri);

    printf("Sto per chiamare gestioneMenu. \n");
    gestioneMenu(clienti, &numeroClienti, ordini, &numeroOrdini);

    // Salvataggio dei dati sui file prima di uscire
    salvaClienti(clienti, numeroClienti);
    salvaOrdini(ordini, numeroOrdini);
    salvaLibri(libri, numeroLibri); 

    return 0;
}
