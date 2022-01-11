//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_CLIENTE_H
#define PROJ_LP_CLIENTE_H

#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cliente(int argc, const char * argv[]);

CLIENTE_LISTA * read_file_txt();
void read_file_cliente_bin();

void write_file_cliente_bin();
void write_file_client_txt();

CLIENTE *add_client(char * name, char *address, int n_fiscal, int contact, int day, int month, int year, CLIENTE_LISTA *list);
CLIENTE_LISTA * deleteClient(int nif, CLIENTE_LISTA *list);

void nif_order(CLIENTE_LISTA *list);
void name_order(CLIENTE_LISTA *list);

void print_linked_user();
void add_client_to_tail(CLIENTE *client, CLIENTE_LISTA *list);
void add_client_to_head(CLIENTE *client, CLIENTE_LISTA *list);

void search_nome_client(char *nome, CLIENTE_LISTA * lista);
void search_nif_client(int nif, CLIENTE_LISTA * lista);
void viagem_search(char *nome, CLIENTE_LISTA *lista, char *cidade);
#endif //PROJ_LP_CLIENTE_H
