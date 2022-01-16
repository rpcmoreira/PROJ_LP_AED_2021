#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * Adiciona uma viagem a um cliente
 * @param list - Lista de Clientes
 * @param nome - nome do Cliente
 * @return
 */
CLIENTE_LISTA *add_viagem(CLIENTE_LISTA *list, char *nome) {
    char buff[50];
    int aux;
    CLIENTE *cliente = list->phead;
    while (cliente != NULL) {
        if (strcmp(nome, cliente->nome) == 0) {
            int n = cliente->historico_viagens.nviagens++;

            HISTORICO_VIAGENS *hist_v = (HISTORICO_VIAGENS *) malloc(sizeof(HISTORICO_VIAGENS) * n);
            hist_v->nviagens = n;
            if (cliente->historico_viagens.p_viagem != NULL) {
                cliente->historico_viagens.p_viagem = (VIAGEM *) realloc(cliente->historico_viagens.p_viagem,
                                                                         sizeof(VIAGEM) * n);
            } else cliente->historico_viagens.p_viagem = (VIAGEM *) malloc(sizeof(VIAGEM));

            printf("Quantas cidades visitou? --------- %s\n", cliente->nome);
            gets(buff);
            aux = atoi(buff);
            if (cliente->historico_viagens.nviagens == 1) {
                cliente->historico_viagens.p_viagem->ncidades = aux;
            } else cliente->historico_viagens.p_viagem[n].ncidades = aux;
            printf("Insira as %d cidades que visitou...\n", aux);
            CIDADE *cidade = (CIDADE *) malloc(sizeof(CIDADE) * aux);
            for (int i = 0; i < aux; ++i) {
                gets(buff);
                cidade[i] = search_City(buff);
            }
            cidade->ar_poi->n_poi = 0;
            cidade->ar_poi->p_poi = NULL;
            cliente->historico_viagens.p_viagem[n].city = cidade;

            return list;;
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    printf("User not found\n");
    return list;
}

/**
 * Apaga uma viagem do cliente
 * @param list - lista de Clientes
 * @param nome - nome do cliente
 * @return
 */
CLIENTE_LISTA *delete_viagem(CLIENTE_LISTA *list, char *nome) {
    char buff[50];
    int aux;
    CLIENTE *cliente = list->phead;
    while (cliente != NULL) {
        if (strcmp(nome, cliente->nome) == 0) {
            printf("\nUser : %s\n", nome);
            printf("Realizou %d viagens\n", cliente->historico_viagens.nviagens);
            for (int i = 0; i < cliente->historico_viagens.nviagens; ++i) {
                printf("Viagem %d\n", i);
                VIAGEM *vg = cliente->historico_viagens.p_viagem;
                for (int j = 0; j < vg[i].ncidades; ++j) {
                    printf("%s\n", vg[i].city[j].nome);
                }
                printf("\n");
            }
            printf("\n");
            printf("Que viagem pretende remover?\n");
            aux = atoi(gets(buff));
            for (int i = aux; i < cliente->historico_viagens.nviagens; ++i) {
                cliente->historico_viagens.p_viagem[i] = cliente->historico_viagens.p_viagem[i + 1];
            }
            cliente->historico_viagens.nviagens--;
            realloc(cliente->historico_viagens.p_viagem, sizeof(VIAGEM) * cliente->historico_viagens.nviagens);
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    return list;
}

CLIENTE_LISTA *edit_viagem(CLIENTE_LISTA *list, char *nome, int n, int n_cidades) {             //EDITAR CIDADES DAS VIAGENS
    char buff[50];
    CLIENTE *cliente = list->phead;
    while (cliente != NULL) {
        if (strcmp(nome, cliente->nome) == 0) {
            printf("\nUser : %s\n", nome);
            printf("Realizou %d viagens\n", cliente->historico_viagens.nviagens);
            for (int i = 0; i < cliente->historico_viagens.nviagens; ++i) {
                printf("Viagem %d\n", i);
                VIAGEM *vg = cliente->historico_viagens.p_viagem;
                for (int j = 0; j < vg[i].ncidades; ++j) {
                    printf("%s\n", vg[i].city[j].nome);
                }
                printf("\n");
            }
            if (n_cidades == 0) {
                printf("Edit should not be used for Deletion, Use Delete Viagem Instead\n");
                return list;
            }

            cliente->historico_viagens.p_viagem[n].city = (CIDADE *) realloc(cliente->historico_viagens.p_viagem[n].city, sizeof(CIDADE) * n_cidades);
            cliente->historico_viagens.p_viagem[n].ncidades = n_cidades;

            printf("Insira as %d cidades que quer editar para esta viagem - Viagem %d\n", n_cidades, n);

            for (int i = 0; i < n_cidades; ++i) {
                gets(buff);
                CIDADE city = search_City(buff);
                city.ar_poi->p_poi = NULL;
                city.ar_poi->n_poi = 0;
                cliente->historico_viagens.p_viagem[n].city[i] = city;
            }
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    return list;
}

CLIENTE_LISTA *edit_city_Viagem(CLIENTE_LISTA *list, char *nome, char *cidade, int n, int type) {
    char buff[50];
    CLIENTE *cliente = list->phead;
    CIDADE city = search_City(cidade);
    while (cliente != NULL) {
        if (strcmp(nome, cliente->nome) == 0) {
            break;
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    if (type == 0) {
        for (int i = 0; i <= cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (i == n) {
                int j = cliente->historico_viagens.p_viagem[i].ncidades;
                cliente->historico_viagens.p_viagem[i].ncidades++;
                cliente->historico_viagens.p_viagem[i].city = realloc(cliente->historico_viagens.p_viagem[i].city,
                                                                      sizeof(CIDADE) *
                                                                      cliente->historico_viagens.p_viagem[i].ncidades);
                city.ar_poi->p_poi = NULL;
                city.ar_poi->n_poi = 0;
                cliente->historico_viagens.p_viagem[i].city[j] = city;

                return list;
            }
        }

        return list;
    } else if (type ==
               1) {                                                                                             //EDITAR VIAGEM; REMOVE CIDADE A FUNCIONAR CORRETAMENTE
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (strcmp(city.nome, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0) {
                for (int j = i; j < cliente->historico_viagens.nviagens; ++j) {
                    cliente->historico_viagens.p_viagem[i].city[j] = cliente->historico_viagens.p_viagem[i].city[j + 1];
                }
                cliente->historico_viagens.p_viagem[n].ncidades--;
                cliente->historico_viagens.p_viagem[i].city = (CIDADE *) realloc(cliente->historico_viagens.p_viagem[i].city,
                                                                      sizeof(CIDADE) *
                                                                      cliente->historico_viagens.p_viagem[n].ncidades);
                return list;
            }
        }
    } else if (type ==
               2) {                                                                                //EDITAR VIAGEM; EDITAR CIDADE NA VIAGEM A FUNCIONAR CORRETAMENTE
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (strcmp(city.nome, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0) {
                printf("Pretende Editar %s para que?\n", cidade);
                gets(buff);
                CIDADE new = search_City(buff);
                new.ar_poi->p_poi = NULL;
                new.ar_poi->n_poi = 0;
                cliente->historico_viagens.p_viagem[n].city[i] = new;
                return list;
            }
        }
    } else {
        printf("Type Error!\n");
        return list;
    }
    return list;
}

CLIENTE_LISTA *edit_poi_Viagem(CLIENTE_LISTA *list, char *nome, char *cidade, char *poi, int n, int type){
    char buff[50];
    CLIENTE *cliente = list->phead;
    POI p = search_Poi(poi, cidade);
    while (cliente != NULL) {
        if (strcmp(nome, cliente->nome) == 0) {
            break;
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    if (type == 0) {                                                                                        //add
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
                if(strcmp(cidade, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0){
                    int j = cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi;
                    if(cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi == 0) {
                        cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi++;
                        cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi = (POI *)malloc(sizeof(POI));
                    }else{
                        cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi++;
                        cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi = (POI *) realloc(cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi,
                                                                                                       sizeof(POI)*cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi);                    }
                    cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[j] = p;
                    return list;
                }
            }
        return list;
    } else if (type == 1) {                                                                                             //EDITAR VIAGEM; REMOVE CIDADE A FUNCIONAR CORRETAMENTE
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (i == n) {
            if (strcmp(cidade, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0) {
                for (int j = 0; j < cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi; ++j) {
                    if(strcmp(cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[j].nome, poi) == 0){
                        for (int k = j; k < cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi; ++k) {
                            cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[k] = cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[k+1];
                        }
                    }cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi--;
                    cliente->historico_viagens.p_viagem[i].city[i].ar_poi->p_poi = (POI *) realloc(cliente->historico_viagens.p_viagem[i].city[i].ar_poi->p_poi,
                                                                                                                             sizeof(POI) *
                                                                                                                             cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi);
                    return list;
                }
            }
        }}
    } else if (type ==
               2) {                                                                                //EDITAR VIAGEM; EDITAR CIDADE NA VIAGEM A FUNCIONAR CORRETAMENTE
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (strcmp(cidade, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0) {
                for (int j = 0; j < cliente->historico_viagens.p_viagem[n].city[i].ar_poi->n_poi; ++j) {
                    if(strcmp(poi,cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[j].nome) == 0){
                        printf("Pretende Editar %s para que?\n", poi);
                        gets(buff);
                        POI new = search_Poi(buff, cidade);
                        cliente->historico_viagens.p_viagem[n].city[i].ar_poi->p_poi[j] = new;
                        return list;
                    }
                }
            }
        }
    } else {
        printf("Type Error!\n");
        return list;
    }
    return list;
}