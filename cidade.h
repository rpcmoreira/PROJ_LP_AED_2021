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

int cidade(int agrc, const char *argv[]);

void read_file_cidade_txt();
void read_file_cidade_bin();

CIDADE * add_city(int id, char *info, double latitude, double longitude);
LIST_CIDADES* add_city_list(CIDADE *city, LIST_CIDADES *list)

#endif //PROJ_LP_CIDADE_H
