#include "cidade.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFO 258

int cidade(int argc, const char * argv[]){
    read_file_cidade_txt();
    //read_file_cidade_bin();
}

void read_file_cidade_txt(){
    FILE *file = fopen("../cidade.txt","r");
    int id;
    char descricao[INFO];
    double latitude, longitude;

    if(file == NULL){
        printf("Failed to open file (txt)\n");
        exit(-1);
    }

    fscanf(file, "%d", &id);
    fscanf(file, "%s", descricao);
    fscanf(file, "%lf", &latitude);
    fscanf(file, "%lf", &longitude);
    fclose(file);

    add_city(id, descricao, latitude, longitude);

    //Falta Loop para se tiver mais cidade
}

void read_file_cidade_bin(){
    FILE *file = fopen("../cidade.txt","rb");
    int id = 0;
    char descricao[INFO];
    double latitude, longitude;
    if(file==NULL){
        printf("ErrFailed to open file (bin)\n");
        exit(-1);
    }

    //Falta leitura do ficheiro em binario e loop

    fclose(file);
    add_city(id, descricao, latitude, longitude);
}

CIDADE * add_city(int id, char *info, double latitude, double longitude){
    CIDADE * cidade = (CIDADE *)malloc(sizeof(CIDADE));
    LIST_CIDADES * newList;
    cidade->id=id;
    strcpy(cidade->descricao, info);
    cidade->cc.lat = latitude;
    cidade->cc.log = longitude;

    add_city_list(cidade, newList);
}

LIST_CIDADES* add_city_list(CIDADE *city, LIST_CIDADES *list) {
    if(list->phead==NULL && list->ncidades==0) { // Se não houver elementos inseridos na lista, insere o atual
        list = (LIST_CIDADES *) malloc(sizeof(LIST_CIDADES));
        list->phead = (CIDADE *) city;
        list->ptail = (CIDADE *) city;
        city->pnext = NULL;
    }
    else{
        list->ncidades++;
        list = (LIST_CIDADES *) realloc(list, list->ncidades * sizeof(LIST_CIDADES));
        list->ptail = city;
        city->pnext = NULL;
    }
    return list;
}
