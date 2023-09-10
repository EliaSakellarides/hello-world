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

    int numeroClienti = 20;
    int numeroOrdini = 0;
    int numeroLibri = 20;
    int result = 0;  // Questo manterrà l'eventuale codice di uscita in caso di errore.

    do {
        // === Gestione Clienti ===
        printf("Creazione file binari per clienti...\n");
        FILE *clientiBinFile = fopen("clienti.bin", "r+b");
        if (!clientiBinFile) {
            clientiBinFile = fopen("clienti.bin", "wb");
            if (!clientiBinFile) {
                perror("Errore nell'apertura del file clienti.bin");
                result = 1;
                break;
            }
            inizializzaClienti(clienti);
            fwrite(clienti, sizeof(Cliente), numeroClienti, clientiBinFile);
            printf("File binario 'clienti.bin' creato con successo.\n");
        } else {
            fread(clienti, sizeof(Cliente), numeroClienti, clientiBinFile);
        }
        fclose(clientiBinFile);

        // === Gestione Libri ===
        printf("Gestione file binari per libri...\n");
        FILE *libriBinFile = fopen("libri.bin", "r+b");
        if (!libriBinFile) {
            libriBinFile = fopen("libri.bin", "wb");
            if (!libriBinFile) {
                perror("Errore nell'apertura del file libri.bin");
                result = 1;
                break;
            }
            inizializzaLibri(libri);
            fwrite(libri, sizeof(Libro), numeroLibri, libriBinFile);
            printf("File binario 'libri.bin' creato con successo.\n");
        } else {
            fread(libri, sizeof(Libro), numeroLibri, libriBinFile);
        }
        fclose(libriBinFile);

        // === Gestione Ordini ===
        printf("Creazione file binari per ordini...\n");
        FILE *ordiniBinFile = fopen("ordini.bin", "r+b");
        if (!ordiniBinFile) {
            ordiniBinFile = fopen("ordini.bin", "wb");
            if (!ordiniBinFile) {
                perror("Errore nell'apertura del file ordini.bin");
                result = 1;
                break;
            }
            inizializzaOrdini(clienti, libri, ordini, numeroClienti, numeroLibri);
            numeroOrdini = MAX_ORDINI;
            fwrite(ordini, sizeof(Ordine), numeroOrdini, ordiniBinFile);
            printf("File binario 'ordini.bin' creato con successo.\n");
        } else {
            fread(ordini, sizeof(Ordine), MAX_ORDINI, ordiniBinFile);
        }
        fclose(ordiniBinFile);

        // === Gestione Menu ===
        printf("Sto per chiamare gestioneMenu. \n");
        gestioneMenu(clienti, &numeroClienti, ordini, &numeroOrdini, libri, numeroLibri);

        // === Salvataggio dati sui file ===
        if (salvaClienti(clienti, numeroClienti) == -1) {
            printf("Errore durante il salvataggio dei clienti.\n");
            result = 1;
            break;
        }
        salvaLibri(libri, numeroLibri);
        salvaOrdini(ordini, numeroOrdini);

    } while (0);  // Questo farà in modo che il ciclo venga eseguito solo una volta.

    return result;  // Restituisce 0 se tutto va bene, 1 in caso di errore.
}
