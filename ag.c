//
// Created by Rui on 1/16/2022.
//

#include "ag.h"
#include "math.h"

GERA *g;
PARAM *p;

void ag(CIDADE *list){
    CIDADE *c = list;
    VIAGEM *v = (VIAGEM *)malloc(sizeof(VIAGEM));
    v->ncidades = list->total;
    v->city = c;

    p = (PARAM *)malloc(sizeof(PARAM));
    p->tam_p = 20;
    p->prob_mutacao = 0.01f;
    p->elitism = 0.25f;
    p->num_geracoes = 30;
    p->n_cidades = v->ncidades;

    g = criarPrimeiraGeracao(v, list);
}





double distancia(double x1, double x2, double y1, double y2){
    double dlat = x2 -x1;
    double dlog = y2-y1;

    double dist = sqrt(pow(dlat,2) + pow(dlog,2));

    return dist;
}

GERA * criarPrimeiraGeracao(VIAGEM *v, CIDADE *list){
    GERA * gera = (GERA *)malloc(sizeof(GERA));
    gera->id = 0;
    gera->viagem = v;

    int *city[p->tam_p];
    for (int i = 0; i < p->tam_p; ++i) {
        int inicial = 0;
        city[i] = (int *)malloc(p->n_cidades*sizeof(int));
        for(int j = 0; j < p->n_cidades; ++j) {
            city[i][j] = inicial;
            inicial++;
        }
        for(int j = 0; j < p->n_cidades; ++j) {
            int temp = city[i][j];
            int random = rand() % p->n_cidades;

            city[i][j] = city[i][random];
            city[i][random] = temp;
        }
    }

    double *dist[p->tam_p];
    for (int i = 0; i < p->tam_p; i++) {
        dist[i] = (double *)malloc(p->n_cidades * sizeof(double));
        for(int j = 0; j < p->n_cidades; ++j) {
            if(j == p->n_cidades - 1){
                dist[i][j] = distancia(gera->viagem->city[city[i][j]].cc.lat, gera->viagem->city[0].cc.lat, gera->viagem->city[city[i][j]].cc.log, gera->viagem->city[0].cc.log);
            }else{
                dist[i][j] = distancia(gera->viagem->city[city[i][j]].cc.lat, gera->viagem->city[city[i][j+1]].cc.lat, gera->viagem->city[city[i][j]].cc.log, gera->viagem->city[city[i][j+1]].cc.log);
            }
        }
    }

    double apt[p->tam_p];
    for (int i = 0; i < p->tam_p; ++i) {
        for (int j = 0; j < p->n_cidades; ++j) {
            apt[i] +=  dist[i][j];
        }
        apt[i] = 1/apt[i];
    }
    gera->pnext = NULL;
    gera->distancia = dist;
    gera->rotas = city;
    gera->aptidao = apt;

    for (int i = 0; i < p->tam_p; ++i) {
        for (int j = 0; j < p->n_cidades; ++j) {
            printf("%d ", city[i][j]);
        }
        printf("\t");
        for (int j = 0; j < p->n_cidades; ++j) {
            printf("%f ", dist[i][j]);

        }
        printf("\t");
        printf("%f \n", apt[i]);
    }
    return gera;
}