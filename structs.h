#ifndef PROJ_LP_STRUCTS_H
#define PROJ_LP_STRUCTS_H

#define MAX100 100
#define MAX250 250
#define MAX500 500

typedef struct data{        ///data nascimento
    int dia, mes, ano;
}DATA;

typedef struct coordenadas { ///coordenadas cidade
    double lat, log;
}COORDENADAS;

typedef struct poi{         ///Place of Interest
    char nome[MAX100];
    char descricao[MAX500];
}POI;

typedef struct array_poi{ ///array de pontos de interesse
    POI *p_poi;
    int n_poi;
}ARRAY_POI;

typedef struct cidade{      //Gene
    char nome[MAX250];                 ///Cidade
    char descricao[MAX250];
    COORDENADAS cc;
    ARRAY_POI *ar_poi;
    int total;
}CIDADE;

typedef struct viagem {             ///Viagem
    CIDADE *city;
    int ncidades;
} VIAGEM;

typedef struct historico_viagens { ///Historico Viagens
    VIAGEM *p_viagem;
    int nviagens;
} HISTORICO_VIAGENS;

typedef struct cliente{             ///Cliente
    char nome[MAX100];
    char morada[MAX100];
    int nif;
    int contacto;
    DATA nascimento;
    HISTORICO_VIAGENS historico_viagens;
    struct client *pnext;
}CLIENTE;

typedef struct cliente_lista{       ///Lista de Clientes
    CLIENTE *phead;
    CLIENTE *ptail;
    int nclientes;
}CLIENTE_LISTA;

#endif //PROJ_LP_STRUCTS_H
