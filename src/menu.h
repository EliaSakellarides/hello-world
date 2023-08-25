#ifndef MENU_H
#define MENU_H

#include "cliente.h"
#include "ordine.h"
#include "libro.h"

void mostraMenu();
void gestioneMenu(Cliente clienti[], int* numeroClienti, Ordine ordini[], int* numeroOrdini, Libro libri[], int numeroLibri);

#endif
