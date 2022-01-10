//
// Created by Rui on 1/10/2022.
//

#ifndef PROJ_LP_POI_H
#define PROJ_LP_POI_H

#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_poi(CIDADE *list, char *nome, char *poi_nome, char *descricao);
void delete_poi(CIDADE *list, char *nome, char *poi_nome);
void search_poi(CIDADE *list, char *poi_nome);
void search_poi_cidade(CIDADE *list, char *cidade);
#endif //PROJ_LP_POI_H
