#ifndef RICERCA_H
#define RICERCA_H

#include "ordine.h"
#include "cliente.h"
#include "libro.h"

Ordine* ricercaOrdine(Ordine ordini[], int numeroOrdini, char id[]);
Cliente* ricercaCliente(Cliente clienti[], int numeroClienti, char id[]);
Libro* ricercaLibro(Libro libri[], int numeroLibri, char idOuTitolo[]); // Aggiornata la firma della funzione

#endif
