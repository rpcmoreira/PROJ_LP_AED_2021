#ifndef PROJ_LP_STRUCTS_H
#define PROJ_LP_STRUCTS_H

#define MAX100 100
#define MAX250 250

typedef struct data{
    int dia, mes, ano;
}DATA;

typedef struct coordenadas {
    double lat, log;
}COORDENADAS;

typedef struct poi{         //Place of Interest
    char nome[MAX100];
    char descricao[MAX250];
}POI;

typedef struct array_poi{
    POI *p_poi;
    int n_poi;
}ARRAY_POI;

typedef struct cidade{      //Gene
    int id;                 //Cidade
    char descricao[MAX250];
    COORDENADAS cc;
    ARRAY_POI ar_poi;
    struct cidade *pnext;
}CIDADE;

typedef struct list_cidades{
    CIDADE *phead;
    CIDADE *ptail;
    int ncidades;
} LIST_CIDADES;

typedef struct ar_id_cidade{
    int *p_city;
    int nids;
} AR_ID_CIDADE;

typedef struct viagem {
    AR_ID_CIDADE lista_cidade;
    DATA begin_viagem;
    DATA end_viagem;
} VIAGEM;

typedef struct historico_viagens {
    VIAGEM *p_viagem;
    int nviagens;
} HISTORICO_VIAGENS;

typedef struct cliente{
    char nome[MAX100];
    char morada[MAX100];
    int nif;
    int contacto;
    DATA nascimento;
    HISTORICO_VIAGENS historico_viagens;
    struct client *pnext;
}CLIENTE;

typedef struct cliente_lista{
    CLIENTE *phead;
    CLIENTE *ptail;
    int nclientes;
}CLIENTE_LISTA;

#endif //PROJ_LP_STRUCTS_H
