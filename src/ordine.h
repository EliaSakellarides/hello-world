
#ifndef ORDINE_H
#define ORDINE_H

#include "cliente.h"
#include "libro.h"


#define MAX_ORDINI 100

#define IN_ESECUZIONE 0
#define EVADED 1
#define ANNULLATO 2

typedef enum {
	StatoInserito,
	StatoEvaso,
	StatoAnnullato,
} StatoOrdine;

typedef struct {

    char idOrdine[50];
    Cliente *cliente[50];
    Libro *libro[50];
    int quantita;
    StatoOrdine stato;
} Ordine;



int salvaOrdini(Ordine ordini[], int numeroOrdini);
int aggiungiOrdine(Ordine ordini[], int *numeroOrdini, Ordine nuovoOrdine);
int modificaOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[], Ordine nuovoOrdine);
int cancellaOrdine(Ordine ordini[], int *numeroOrdini, char idOrdine[]);
void visualizzaOrdini(const Ordine ordini[], int numeroOrdini);
void caricaOrdini(Ordine ordini[], int* numeroOrdini, int maxSize);
int evadiOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[]);
const char* statoToString(StatoOrdine stato);


#endif
