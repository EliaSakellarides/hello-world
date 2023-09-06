#include "menu.h"
#include "ordine.h"
#include "libro.h"
#include "ricerca.h"
#include "algoritmoOrdinamento.h"
#include "util.h"
#include <stdio.h>
#include "cliente.h"

void mostraMenu() {
    // Mostra il menu
    printf("--- Menù ---\n");
    printf("1. Aggiungi cliente\n");
    printf("2. Modifica cliente\n");
    printf("3. Cancella cliente\n");
    printf("4. Visualizza clienti\n");
    printf("5. Aggiungi ordine\n");
    printf("6. Modifica ordine\n");
    printf("7. Cancella ordine\n");
    printf("8. Visualizza ordini\n");
    printf("9. Evadi ordine\n");
    printf("10. Visualizza tutti i libri\n");
    printf("0. Esci\n");
    printf("Scegli un'opzione: ");
}

void gestioneMenu(Cliente clienti[], int* numeroClienti, Ordine ordini[], int* numeroOrdini, Libro libri[], int numeroLibri) {
    int scelta;
    Libro *libroSelezionato = NULL;
    Cliente nuovoCliente = {0};
    Ordine nuovoOrdine = {0};
    char idCliente[10];
    char idOrdine[10];

    do {
        mostraMenu();
        char bufferScelta[10];  //
        leggiRiga(bufferScelta, sizeof(bufferScelta));
        sscanf(bufferScelta, "%d", &scelta);
        fflush(stdin); // Pulizia del buffer di input

        switch (scelta) {
        case 1:
            printf("Inserisci le informazioni del nuovo cliente:\n");
            printf("Inserisci l'ID del cliente: (si prega di utilizzare un ID simile C01,C02 ecc. ");
            leggiRiga(nuovoCliente.idCliente, sizeof(nuovoCliente.idCliente));
            printf("Inserisci il nome, ");
            leggiRiga(nuovoCliente.nome, sizeof(nuovoCliente.nome));
            printf("Inserisci il cognome: ");
            leggiRiga(nuovoCliente.cognome, sizeof(nuovoCliente.cognome));
            aggiungiCliente(clienti, numeroClienti, &nuovoCliente);
            break;

        case 2:
            printf("Inserisci l'ID del cliente da modificare:\n");
            leggiRiga(idCliente, sizeof(idCliente));

            char newNome[50], newCognome[50];
            printf("Inserisci il nuovo nome (lascia vuoto per non modificare):\n");
            leggiRiga(newNome, sizeof(newNome));

            printf("Inserisci il nuovo cognome (lascia vuoto per non modificare):\n");
            leggiRiga(newCognome, sizeof(newCognome));

            modificaCliente(clienti, *numeroClienti, idCliente, newNome, newCognome);
            break;

        case 3:
            printf("Inserisci l'ID del cliente da cancellare:\n");
            leggiRiga(idCliente, sizeof(idCliente)); // using leggiRiga instead of scanf
            cancellaCliente(clienti, numeroClienti, idCliente);
            break;

        case 4:
            visualizzaClienti(clienti, *numeroClienti);
            break;

        case 5:
            printf("Inserisci le informazioni del nuovo ordine:\n");
            printf("Elenco degli ISBN dei libri:\n");
            for (int i = 0; i < numeroLibri; i++) {
                printf("%s\n", libri[i].isbn);
            }
            char isbnInserito[20]; // Assumi un massimo di 20 caratteri per l'ISBN
            printf("Inserisci l'ISBN del libro: ");
            leggiRiga(isbnInserito, sizeof(isbnInserito));

            libroSelezionato = ricercaLibro(libri, numeroLibri, isbnInserito);

            if (libroSelezionato) {
                printf("Libro trovato: %s\n", libroSelezionato->titolo);
                // Aggiungi la logica per continuare a elaborare l'ordine
            } else {
                printf("Libro non trovato.\n");
                break;
            }

            printf("Inserisci l'ID del cliente che effettua l'ordine: ");
            leggiRiga(idCliente, sizeof(idCliente));

            // Ricerca il cliente...
            Cliente *clienteSelezionato = ricercaCliente(clienti, *numeroClienti, idCliente);

            if (clienteSelezionato == NULL) {
                printf("Cliente non trovato.\n");
                break;
            }

            nuovoOrdine.cliente = clienteSelezionato;  // Assegna direttamente il puntatore clienteSelezionato
            nuovoOrdine.libro = libroSelezionato;      // Assegna direttamente il puntatore libroSelezionato

            aggiungiOrdine(ordini, numeroOrdini, nuovoOrdine);
            break;

        case 6:
            printf("Inserisci l'ID dell'ordine da modificare:\n");
            leggiRiga(idOrdine, sizeof(idOrdine)); // using leggiRiga instead of scanf
            printf("Inserisci le nuove informazioni dell'ordine:\n");
            // Input per le nuove informazioni dell'ordine...
            modificaOrdine(ordini, *numeroOrdini, idOrdine, nuovoOrdine);
            break;

        case 7:
            printf("Inserisci l'ID dell'ordine da cancellare:\n");
            leggiRiga(idOrdine, sizeof(idOrdine)); // using leggiRiga instead of scanf
            cancellaOrdine(ordini, numeroOrdini, idOrdine);
            break;

        case 8:
            fflush(stdin); // Pulizia del buffer di input
            visualizzaOrdini(ordini, *numeroOrdini);
            break;

        case 9:
            printf("Inserisci l'ID dell'ordine da evadere:\n");
            leggiRiga(idOrdine, sizeof(idOrdine));
            evadiOrdine(ordini, *numeroOrdini, idOrdine);
            break;

        case 10:
            visualizzaLibri(libri, numeroLibri);
            break;

        case 0:
            printf("Uscita...\n");
            break;

        default:
            printf("Opzione non valida. Riprova.\n");
        }
    } while (scelta != 0);
}
