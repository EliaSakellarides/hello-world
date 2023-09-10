#ifndef ALGORITMO_ORDINAMENTO_H
#define ALGORITMO_ORDINAMENTO_H

#include "ordine.h"
#include "cliente.h"
#include "libro.h"

// Funzioni di comparazione
int compareOrdini(const Ordine* a, const Ordine* b);
int compareClienti(const Cliente* a, const Cliente* b);
int compareLibri(const Libro* a, const Libro* b);
void ordinaEVisualizzaLibri(Libro libri[], int numeroLibri);


// Funzioni QuickSort per Ordini
void quickSortOrdini(Ordine ordini[], int primo, int ultimo);

// Funzioni QuickSort per Clienti
void quickSortClienti(Cliente clienti[], int primo, int ultimo);

// Funzioni QuickSort per Libri
void quickSortLibri(Libro libri[], int primo, int ultimo);

#endif
