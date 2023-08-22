#include "menu.h"
#include "ordine.h"
#include "libro.h"
#include "ricerca.h"
#include "algoritmoOrdinamento.h"
#include "util.h"
#include <stdio.h>

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
    printf("0. Esci\n");
    printf("Scegli un'opzione: ");
}

void gestioneMenu(Cliente clienti[], int* numeroClienti, Ordine ordini[], int* numeroOrdini) {
    int scelta;
    do {
    		mostraMenu();
    	    scanf("%d", &scelta);
    	    pulisciBuffer();

        Cliente nuovoCliente = {0};
        Ordine nuovoOrdine = {0};
        char idCliente[10];
        char idOrdine[10];

        switch (scelta) {
            case 1:
                printf("Inserisci le informazioni del nuovo cliente:\n");
                // Input per il nuovo cliente...
                aggiungiCliente(clienti, numeroClienti, nuovoCliente);
                break;
            case 2:
                printf("Inserisci l'ID del cliente da modificare:\n");
                scanf("%s", idCliente);
                printf("Inserisci le nuove informazioni del cliente:\n");
                // Input per le nuove informazioni del cliente...
                modificaCliente(clienti, *numeroClienti, idCliente, nuovoCliente);
                break;
            case 3:
                printf("Inserisci l'ID del cliente da cancellare:\n");
                scanf("%s", idCliente);
                cancellaCliente(clienti, numeroClienti, idCliente);
                break;
            case 4:
                visualizzaClienti(clienti, *numeroClienti);
                break;
            case 5:
                printf("Inserisci le informazioni del nuovo ordine:\n");
                // Input per il nuovo ordine...
                aggiungiOrdine(ordini, numeroOrdini, nuovoOrdine);
                break;
            case 6:
                printf("Inserisci l'ID dell'ordine da modificare:\n");
                scanf("%s", idOrdine);
                printf("Inserisci le nuove informazioni dell'ordine:\n");
                // Input per le nuove informazioni dell'ordine...
                modificaOrdine(ordini, *numeroOrdini, idOrdine, nuovoOrdine);
                break;
            case 7:
                printf("Inserisci l'ID dell'ordine da cancellare:\n");
                scanf("%s", idOrdine);
                cancellaOrdine(ordini, numeroOrdini, idOrdine);
                break;
            case 8:
                visualizzaOrdini(ordini, *numeroOrdini);
                break;
            case 9:
                printf("Inserisci l'ID dell'ordine da evadere:\n");
                scanf("%s", idOrdine);
                evadiOrdine(ordini, *numeroOrdini, idOrdine);
                break;
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Opzione non valida. Riprova.\n");
        }
        	} while (scelta != 0);
}
