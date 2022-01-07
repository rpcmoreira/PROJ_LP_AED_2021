#include "cidade.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFO 258

void cidade(int argc, const char * argv[]){
    //read_file_cidade_txt();
    //read_file_cidade_bin();
    LIST_CIDADES *list = (LIST_CIDADES *)malloc(sizeof(LIST_CIDADES));
    list->phead = list->ptail = NULL;
    list->ncidades = 0;
    add_city(1,"Porto e uma cidade no norte", 3657.27, 6732.2,list);
    add_city(2,"Lisboa e uma cidade no centro", 11111.11, 22222.22,list);
    add_city(3,"Faro e uma cidade no sul", 44444.44, 66666.66,list);
    add_city(4,"FCP 3-1 SLB", 5435434, 123213,list);
    add_city(5,"Sbording", 2313.6, 32331.6,list);
    print_linked_cidade(list);
}

void read_file_cidade_txt(LIST_CIDADES *list){
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

    add_city(id, descricao, latitude, longitude, list);

    //Falta Loop para se tiver mais cidade
}

void read_file_cidade_bin(LIST_CIDADES *list){
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
    add_city(id, descricao, latitude, longitude, list);
}

CIDADE * add_city(int id, char *info, double latitude, double longitude, LIST_CIDADES * newList){
    CIDADE * cidade = (CIDADE *)malloc(sizeof(CIDADE));
    cidade->id=id;
    strcpy(cidade->descricao, info);
    cidade->cc.lat = latitude;
    cidade->cc.log = longitude;

    add_city_list(cidade, newList);
    return cidade;
}

LIST_CIDADES * add_city_list(CIDADE *city, LIST_CIDADES *list) {
    if(list->phead==NULL && list->ncidades==0) { // Se não houver elementos inseridos na lista, insere o atual
        list->phead = (CIDADE *) city;
        list->ptail = (CIDADE *) city;
        list->ncidades++;
        city->pnext = NULL;
    }
    else{
        list->ncidades++;
        list->ptail->pnext = (CIDADE *) city;
        list->ptail = city;
        list->ptail->pnext = NULL;
    }
    return list;
}

void print_linked_cidade(LIST_CIDADES *head) {
    LIST_CIDADES *current_node = head;
    CIDADE *print = (CIDADE *) head->phead;
    while (print != NULL) {
        printf("%d\n", print->id);
        printf("%s\n", print->descricao);
        printf("%lf\n", print->cc.log);
        printf("%lf\n", print->cc.lat);

        print = print->pnext;
    }
}
