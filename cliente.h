//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_CLIENTE_H
#define PROJ_LP_CLIENTE_H

#include "structs.h"

void read_file_cliente_txt();
void read_file_cliente_bin();


CLIENTE *add_client_tail(char * name, char *address, int n_fiscal, int contact, int day, int month, int year);
CLIENTE *add_client_head(char * name, char *address, int n_fiscal, int contact, int day, int month, int year);
void add_to_tail(CLIENTE *client, CLIENTE_LISTA *list);
void add_to_head(CLIENTE *client, CLIENTE_LISTA *list);

CLIENTE_LISTA * deleteClient(int nif);
#endif //PROJ_LP_CLIENTE_H
