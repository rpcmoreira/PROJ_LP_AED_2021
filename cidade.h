//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_CIDADE_H
#define PROJ_LP_CIDADE_H

#include "cidade.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cidade(int agrc, const char *argv[]);

CIDADE * read_file_cidade_txt();
void read_file_cidade_bin(CIDADE *list);

CIDADE * add_city(char *nome, char *descricao, double latitude, double longitude, ARRAY_POI *poi, int pos, CIDADE * list);
CIDADE * add_city_list(CIDADE *city, CIDADE *list);

CIDADE search_City(char *name);
void print_linked_cidade(CIDADE *head);

#endif //PROJ_LP_CIDADE_H
