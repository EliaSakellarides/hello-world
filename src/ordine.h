
#ifndef ORDINE_H
#define ORDINE_H

#include "cliente.h"
#include "libro.h"


#define MAX_ORDINI 100
#define MAX_ID_ORDINE 10


#define IN_ESECUZIONE 0
#define EVADED 1
#define ANNULLATO 2

typedef enum {
	StatoInserito,
	StatoEvaso,
	StatoAnnullato,
} StatoOrdine;

typedef struct {
	char idOrdine[10];
	char idCliente[MAX_ID + 1];
	char idLibro[20];
	char isbn[20];
	Cliente* cliente;
	Libro* libro;
    int quantita;
    StatoOrdine stato;
} Ordine;


void inizializzaOrdini(const Cliente clienti[], const Libro libri[], Ordine ordini[], int numeroClienti, int numeroLibri);
int salvaOrdini(Ordine ordini[], int numeroOrdini);
int aggiungiOrdine(Ordine ordini[], int *numeroOrdini, Ordine nuovoOrdine);
int modificaOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[], Ordine nuovoOrdine);
int cancellaOrdine(Ordine ordini[], int *numeroOrdini, char idOrdine[]);
void visualizzaOrdini(const Cliente clienti[], int numeroClienti, const Ordine ordini[], int numeroOrdini, const Libro libri[], int numeroLibri);
void caricaOrdini(Ordine ordini[], int* numeroOrdini, int maxSize);
int evadiOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[]);
const char* statoToString(StatoOrdine stato);


#endif
