#ifndef RICERCA_H
#define RICERCA_H

#include "ordine.h"
#include "cliente.h"
#include "libro.h"

/**
 * Searches for an order using its ID.
 *
 * @param ordini The array of orders.
 * @param numeroOrdini The number of orders in the array.
 * @param id The ID of the order to be searched.
 * @return A pointer to the order if found; otherwise, NULL.
 */
Ordine* ricercaOrdine(Ordine ordini[], int numeroOrdini, char id[]);

/**
 * Searches for a customer using their ID.
 *
 * @param clienti The array of customers.
 * @param numeroClienti The number of customers in the array.
 * @param id The ID of the customer to be searched.
 * @return A pointer to the customer if found; otherwise, NULL.
 */
Cliente* ricercaCliente(Cliente clienti[], int numeroClienti, const char id[]);

/**
 * Searches for a book using its ISBN.
 *
 * @param libri The array of books.
 * @param numeroLibri The number of books in the array.
 * @param isbn The ISBN of the book to be searched.
 * @return A pointer to the book if found; otherwise, NULL.
 */
Libro* ricercaLibro(Libro libri[], int numeroLibri, char isbn[]);

#endif
