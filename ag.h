#ifndef PROJ_LP_AG_H
#define PROJ_LP_AG_H
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct param{ ///parametros
    int tam_p;
    float prob_mutacao;
    float elitism;
    int num_geracoes;
    int n_cidades;
}PARAM;

typedef struct gera{ ///geracao
    int id;
    int **rotas;
    double *aptidao;
    VIAGEM *viagem;
    double **distancia;
    struct gera *pnext;
}GERA;

void ag(CIDADE *list);
double distancia(double x1, double x2, double y1, double y2);
GERA * criarPrimeiraGeracao(VIAGEM *v, CIDADE *list);
double graus_para_radianos(double deg);
int **geraElitismo(GERA *gera, float f, int n);

#endif //PROJ_LP_AG_H