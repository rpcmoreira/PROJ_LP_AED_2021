//
// Created by Rui on 1/10/2022.
//

#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_poi(CIDADE *list, char *nome, char *poi_nome, char *descricao) {
    for (int i = 0; i < list->total; ++i) {
        if (strcmp(list[i].nome, nome) == 0) {
            for (int j = 0; j <= list[i].ar_poi->n_poi; j++) {
                if (list[i].ar_poi->n_poi != 0) {
                    list[i].ar_poi->n_poi++;
                    list[i].ar_poi->p_poi = (POI *) realloc(list[i].ar_poi->p_poi, sizeof(POI) * list[i].ar_poi->n_poi);
                } else {
                    list[i].ar_poi->n_poi++;
                    list[i].ar_poi->p_poi = (POI *) malloc(sizeof(POI) * list[i].ar_poi->n_poi);
                }

                POI *poi = malloc(sizeof(POI));
                strcpy(poi->nome, poi_nome);
                strcpy(poi->descricao, descricao);

                list[i].ar_poi[j].p_poi = poi;
                return;
            }
        }
    }
    printf("City doesn't exist..\n");
    exit(-1);
}

void delete_poi(CIDADE *list, char *nome, char *poi_nome) {
    int t = 0;
    for (t; t < list->total; ++t) {
        if (strcmp(list[t].nome, nome) == 0) {
            break;
        }
    }
    for (int i = 0; i < list[i].ar_poi->n_poi; ++i) {
        if (strcmp(list[t].ar_poi[i].p_poi->nome, poi_nome) == 0) {
            for (int j = i; j < list[t].ar_poi->n_poi; ++j) {
                list[t].ar_poi[j].p_poi = list[t].ar_poi[j + 1].p_poi;
            }

            list[t].ar_poi->n_poi--;
            realloc(list[t].ar_poi[i].p_poi, sizeof(POI) * list[t].ar_poi->n_poi);
            return;
        }
    }
}

void search_poi(CIDADE *list, char *poi_nome) {                                         // Search PoI a funcionar
    for (int j = 0; j < list->total; ++j) {
        for (int i = 0; i < list[j].ar_poi->n_poi; ++i) {
            if (strcmp(poi_nome, list[j].ar_poi[i].p_poi->nome) == 0) {
                printf("Found a PoI named %s\n", poi_nome);
                printf("Belongs to the city of %s\n", list[j].nome);
                printf("%s\n\n", list[j].ar_poi[i].p_poi->descricao);
                break;
            }
        }
    }


}
