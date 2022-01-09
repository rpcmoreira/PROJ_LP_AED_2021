#include "cidade.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define null NULL

#define INFO 258
CIDADE * list = NULL;

void cidade(int argc, const char * argv[]){

    list = read_file_cidade_txt();
}

CIDADE * read_file_cidade_txt(){
    FILE *file;
    char nome[MAX100], descricao[MAX100], nome_poi[MAX100], desc_poi[MAX100];
    float lat,log;
    char temp[20];
    int n, tam;
    if ((file = fopen("../data/cidade.txt", "r")) == NULL) {
        printf("fopen cidade.txt failed, exiting now...\n");
        exit(-1);
    }

    fscanf(file, "%d\n", &tam);
    CIDADE * list = (CIDADE *)malloc(sizeof(CIDADE)*tam);
    for (int i = 0; i < tam; ++i) {
        fscanf(file, "%[^,],", list[i].nome);
        fscanf(file, "%[^,],", list[i].descricao);
        fscanf(file, "%[^,],", temp);
        list[i].cc.log = atof(temp);
        fscanf(file, "%[^,],", temp);
        list[i].cc.lat = atof(temp);
        fscanf(file, "%[^\n]\n", temp);
        n = atoi(temp);
        list[i].total = tam;
        ARRAY_POI * arr_poi = (ARRAY_POI *)malloc(sizeof(ARRAY_POI)*n);
        for (int j = 0; j < n; ++j) {
            POI * poi = (POI *)malloc(sizeof(POI));
            fscanf(file, "%[^,],", nome_poi);
            fscanf(file, "%[^\n]\n", desc_poi);

            arr_poi[j].p_poi = poi;
        }
        list[i].ar_poi = arr_poi;
    }
  fclose(file);
    return list;
}

void read_file_cidade_bin(CIDADE *list){
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
    //add_city(id, descricao, latitude, longitude, list);
}

CIDADE * add_city(char *nome, char *descricao, double latitude, double longitude, ARRAY_POI *poi, int pos, CIDADE * list){
    if(list == NULL){
        list = (CIDADE *)malloc(sizeof(CIDADE));
    }else{
        list = (CIDADE *)realloc(list, sizeof(CIDADE)*pos);
    }
    strcpy(list[pos].nome, nome);
    strcpy(list[pos].descricao, descricao);
    list[pos].cc.lat = latitude;
    list[pos].cc.log = longitude;
    list[pos].ar_poi = poi;
    list[pos].total = pos;
    return list;
}

void print_linked_cidade(CIDADE *head) {
    for (int i = 0; i < head->total; ++i) {
        printf("%s\n", head[i].nome);
        printf("%s\n", head[i].descricao);
        printf("%lf\n", head[i].cc.log);
        printf("%lf\n", head[i].cc.lat);
        for (int j = 0; j < head[i].ar_poi[j].n_poi; ++j) {
            printf("%s, %s\n", head[i].ar_poi[j].p_poi->nome,head[i].ar_poi[j].p_poi->descricao);
        }
    }
}

CIDADE search_City(char *name){
    for (int i = 0; i < list->total; ++i) {
        if(strcmp(list[i].nome, name) == 0){
            return list[i];
        }
    }
    printf("Nao encontrei cidade...\n");
    exit(-1);
}
