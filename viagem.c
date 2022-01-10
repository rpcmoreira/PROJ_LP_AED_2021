#include "cliente.h"
#include "structs.h"
#include "cidade.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

CLIENTE_LISTA * add_viagem(CLIENTE_LISTA *list, char *nome){
    char buff[50];
    int aux;
    CLIENTE *cliente = list->phead;
    while(cliente != NULL){
        if(strcmp(nome, cliente->nome) == 0){
            int n =  cliente->historico_viagens.nviagens++;

            HISTORICO_VIAGENS *hist_v = (HISTORICO_VIAGENS *)malloc(sizeof(HISTORICO_VIAGENS)*n);
            hist_v->nviagens = n;
            if(cliente->historico_viagens.p_viagem != NULL){
                cliente->historico_viagens.p_viagem = (VIAGEM *)realloc(cliente->historico_viagens.p_viagem, sizeof(VIAGEM)*n);
            }
            else cliente->historico_viagens.p_viagem = (VIAGEM *)malloc(sizeof(VIAGEM));

            printf("Quantas cidades visitou? --------- %s\n", cliente->nome);
            gets(buff); aux = atoi(buff);
            if(cliente->historico_viagens.nviagens == 1){
                cliente->historico_viagens.p_viagem->ncidades = aux;
            }
            else cliente->historico_viagens.p_viagem[n].ncidades = aux;
            printf("Insira as %d cidades que visitou...\n", aux);
            CIDADE * cidade =(CIDADE *)malloc(sizeof(CIDADE)*aux);
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

CLIENTE_LISTA * delete_viagem(CLIENTE_LISTA *list, char *nome){
    char buff[50];
    int aux;
    CLIENTE *cliente = list->phead;
    while(cliente != NULL){
        if(strcmp(nome, cliente->nome) == 0){
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
                cliente->historico_viagens.p_viagem[i] = cliente->historico_viagens.p_viagem[i+1];
            }
            cliente->historico_viagens.nviagens--;
            realloc(cliente->historico_viagens.p_viagem, sizeof(VIAGEM)*cliente->historico_viagens.nviagens);
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    return list;
}