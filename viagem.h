//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_VIAGEM_H
#define PROJ_LP_VIAGEM_H

#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

CLIENTE_LISTA * add_viagem(CLIENTE_LISTA *list, char *nome);
CLIENTE_LISTA * delete_viagem(CLIENTE_LISTA *list, char *nome);
CLIENTE_LISTA * edit_city_Viagem(CLIENTE_LISTA *list, char *nome, char *Cidade, int n, int type);
CLIENTE_LISTA * edit_viagem(CLIENTE_LISTA *list, char *nome, int n, int n_cidades);
#endif //PROJ_LP_VIAGEM_H
