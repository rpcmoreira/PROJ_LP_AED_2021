//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_CLIENTE_H
#define PROJ_LP_CLIENTE_H

#include "structs.h"

void cliente(int argc, const char * argv[]);

CLIENTE_LISTA * read_file_txt();

void read_file_cliente_bin();
void write_file_client_txt(CLIENTE_LISTA *list, char* path);
CLIENTE *add_client(char * name, char *address, int n_fiscal, int contact, int day, int month, int year, CLIENTE_LISTA *list);
void add_client_to_tail(CLIENTE *client, CLIENTE_LISTA *list);
void add_client_to_head(CLIENTE *client, CLIENTE_LISTA *list);
CLIENTE_LISTA * deleteClient(int nif, CLIENTE_LISTA *list);
void nif_order(CLIENTE_LISTA *list);
void print_linked_user(CLIENTE_LISTA *head);

#endif //PROJ_LP_CLIENTE_H
