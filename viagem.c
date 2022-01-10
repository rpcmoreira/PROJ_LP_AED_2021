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
            HISTORICO_VIAGENS hist_v = cliente->historico_viagens;
            for (int i = 0; i < hist_v.nviagens; ++i) {
                printf("\nViagem %d\n", i);
                VIAGEM *viagem = cliente->historico_viagens.p_viagem;
                for (int j = 0; j < viagem->ncidades; ++j) {
                    CIDADE cidade = viagem[i].city[j];
                    printf("%s - ", cidade.nome);
                }
            }
            
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    return list;
}