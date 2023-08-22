#include "ricerca.h"
#include "ordine.h"
#include "cliente.h"
#include "libro.h"
#include <string.h>

Ordine* ricercaOrdine(Ordine ordini[], int numeroOrdini, char id[]) {
    for (int i = 0; i < numeroOrdini; i++) {
    	if (strcmp(ordini[i].idOrdine, id) == 0) {
            return &ordini[i];
        }
    }
    return NULL; // non trovato
}

Cliente* ricercaCliente(Cliente clienti[], int numeroClienti, char id[]) {
    for (int i = 0; i < numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            return &clienti[i];
        }
    }
    return NULL; // non trovato
}

Libro* ricercaLibro(Libro libri[], int numeroLibri, char isbn[]) {
    for (int i = 0; i < numeroLibri; i++) {
        if (strcmp(libri[i].isbn, isbn) == 0) {
            return &libri[i];
        }
    }
    return NULL; // non trovato
}
