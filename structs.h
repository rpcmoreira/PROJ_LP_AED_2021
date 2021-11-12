#ifndef PROJ_LP_STRUCTS_H
#define PROJ_LP_STRUCTS_H
#define MAX 50

typedef struct poi{         //Place of Interest
    char nome[50];
}POI;

typedef struct cidade{      //Gene
    int id;                 //Cidade
    float cX;
    float cY;
    POI *poi;
}CIDADE;

typedef struct viagens{     //Viagens feitas pelo Cliente
    CIDADE *visita;
}VIAGENS;

typedef struct cliente{     //Cliente, tem linked list de viagens, nome e nif
    int nif;
    char nome[MAX];
    VIAGENS *viagens;
}CLIENTE;

typedef struct pais{        //Pais, conjunto de cidades e nome
    char nome[MAX];
    CIDADE *cidades;
}PAIS;

typedef struct trajeto{     //Individuo (Ruas), tem a cidade de inicio e a cidade do fim + a distancia
    CIDADE cityBegin;
    CIDADE cityEnd;
    float distancia;
}TRAJETO;

#endif //PROJ_LP_STRUCTS_H
