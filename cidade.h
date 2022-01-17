//
// Created by Rui on 1/1/2022.
//

#ifndef PROJ_LP_CIDADE_H
#define PROJ_LP_CIDADE_H

#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ag.h"

void cidade(int agrc, const char *argv[]);

void read_file_cidade_txt();
void write_file_cidade_txt();
void read_file_cidade_bin();
void write_file_cidade_bin();

CIDADE * add_city(char *nome, char *descricao, double latitude, double longitude, ARRAY_POI *poi, int pos, CIDADE * list);
CIDADE * add_city_list(CIDADE *city, CIDADE *list);
void add_City(char *nome, char *descricao, float lat, float log);
void edit_cidade(CIDADE * city, float lat, float log, char *desc, char *cidade, int type);

CIDADE search_City(char *name);
void binarySearchCidades(CIDADE *list, char *nome);

POI search_Poi(char *poi, char *cidade);

CIDADE * insertionSort(CIDADE *cidade);
CIDADE *trocaPos(CIDADE pCidade, CIDADE pCidade1);

void print_all_city();
void print_city(char *city);

#endif //PROJ_LP_CIDADE_H
