//
// Created by Rui on 1/16/2022.
//

#include "ag.h"
#include "math.h"

GERA *g;
GERA *aux;
PARAM *p;


/**
 * Comeca o AG com a lista de cidades
 * @param list
 */
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

    aux = g;
    for (int i = 1; i < p->num_geracoes; ++i) {
        GERA *new = (GERA *)malloc(sizeof(GERA));
        new->id = aux->id+1;
        geraElitismo(aux, p->elitism, p->tam_p);
    }
}




/**
 * Distancia entre dois pontos
 * @param x1 - latitude cidade 1
 * @param x2 - latitude cidade 2
 * @param y1 - longitude cidade 1
 * @param y2 - longitude cidade 2
 * @return
 */
double distancia(double x1, double x2, double y1, double y2){
    double dlat = x2 -x1;
    double dlog = y2-y1;

    double dist = sqrt(pow(dlat,2) + pow(dlog,2));

    return dist;
}

/**
 * Primeira geracao criada
 * @param v - viagem
 * @param list - lista de cidades
 * @return
 */
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
            //printf("%d ", city[i][j]);
        }
        //printf("\t");
        for (int j = 0; j < p->n_cidades; ++j) {
            //printf("%f ", dist[i][j]);

        }
        //printf("\t");
        //printf("%f \n", apt[i]);
    }
    return gera;
}

/**
 * Verifica elitismo e quais vai prosseguir
 * @param gera - geracao
 * @param f - elitismo
 * @param n - n total de individuos
 * @return
 */
void geraElitismo(GERA *gera, float f, int n) {
    int first = 0, second = 0, third = 0, fourth = 0, fifth = 0;
    for (int i = 0; i < n; ++i) {
        if (gera->aptidao[first] < gera->aptidao[i] || first == 0) {
            fifth = fourth;
            fourth = third;
            third = second;
            second = first;
            first = i;
        } else if (gera->aptidao[second] < gera->aptidao[i] || second == 0) {
            fifth = fourth;
            fourth = third;
            third = second;
            second = i;
        } else if (gera->aptidao[first] < gera->aptidao[i] || third == 0) {
            fifth = fourth;
            fourth = third;
            third = i;
        } else if (gera->aptidao[first] < gera->aptidao[i] || fourth == 0) {
            fifth = fourth;
            fourth = i;
        } else if (gera->aptidao[first] < gera->aptidao[i] || fifth == 0) {
            fifth = i;
        }
    }
    int eliteaux[] = {first, second, third, fourth, fifth};

    for (int i = 0; i < 5; ++i) {
        printf("%d\n", eliteaux[i]);
    }
    int t = (int) ((float) n / f);
    int *elite[t];
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < p->n_cidades; ++j) {
            elite[i][j] = gera->rotas[eliteaux[i]][j];
        }
    }

    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < p->n_cidades; ++j) {
            printf("%d ", elite[i][j]);
        }
        printf("\n");
    }
}