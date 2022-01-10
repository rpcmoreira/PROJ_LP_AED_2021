#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
            cliente->historico_viagens.p_viagem[n].city = cidade;

            break;
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    return list;
}

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

CLIENTE_LISTA *
edit_viagem(CLIENTE_LISTA *list, char *nome, int n, int n_cidades) {             //EDITAR CIDADES DAS VIAGENS
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
            if (n_cidades == 0) {
                printf("Edit should not be used for Deletion, Use Delete Viagem Instead\n");
                return list;
            }
            cliente->historico_viagens.p_viagem[n].ncidades = n_cidades;
            realloc(cliente->historico_viagens.p_viagem[n].city, sizeof(CIDADE) * n_cidades);

            printf("Insira as %d cidades que quer editar para esta viagem - Viagem %d\n", n_cidades, n);

            for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
                gets(buff);
                CIDADE city = search_City(buff);
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
        printf("%d\n", cliente->historico_viagens.p_viagem[n].ncidades);
        cliente->historico_viagens.p_viagem[n].ncidades++;
        realloc(cliente->historico_viagens.p_viagem[n].city, cliente->historico_viagens.p_viagem[n].ncidades);
        printf("%d\n", cliente->historico_viagens.p_viagem[n].ncidades);
        cliente->historico_viagens.p_viagem[n].city[cliente->historico_viagens.p_viagem[n].ncidades - 1] = city;

        return list;
    } else if (type ==
               1) {                                                                                 //EDITAR VIAGEM; REMOVE CIDADE A FUNCIONAR CORRETAMENTE
        for (int i = 0; i < cliente->historico_viagens.p_viagem[n].ncidades; ++i) {
            if (strcmp(city.nome, cliente->historico_viagens.p_viagem[n].city[i].nome) == 0) {
                for (int j = i; j < cliente->historico_viagens.nviagens; ++j) {
                    cliente->historico_viagens.p_viagem[i].city[j] = cliente->historico_viagens.p_viagem[i].city[j + 1];
                }
                cliente->historico_viagens.p_viagem[n].ncidades--;
                cliente->historico_viagens.p_viagem[i].city = realloc(cliente->historico_viagens.p_viagem[i].city,
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
                cliente->historico_viagens.p_viagem[n].city[i] = new;
                return list;
            }
        }
    } else {
        printf("Type Error!\n");
        return list;
    }
}
