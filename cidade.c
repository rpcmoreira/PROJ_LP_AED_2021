#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define null NULL

#define INFO 258

CIDADE * list;

void cidade(int argc, const char * argv[]){
    list = (CIDADE *)malloc(sizeof(CIDADE));
    list->total = 0;
    read_file_cidade_txt();

    //add_City("Lamego", "Cidade de Lamego", 43.32f, 21.12f);

    //add_poi(list, "Lamego", "Castelo de Lamego", "Castelo da Cidade de Lamego");
    //delete_poi(list, "Lisboa", "Oceanario de Lisboa");
    search_poi(list, "Estadio do Dragao");

    print_city();



}

void read_file_cidade_txt(){
    FILE *file;
    char nome_poi[MAX100], desc_poi[MAX100];
    char temp[20];
    int n, tam;
    if ((file = fopen("../data/cidade.txt", "r")) == NULL) {
        printf("fopen cidade.txt failed, exiting now...\n");
        exit(-1);
    }

    fscanf(file, "%d\n", &tam);
    list = (CIDADE *)realloc(list, sizeof(CIDADE)*tam);
    for (int i = 0; i < tam; ++i) {
        fscanf(file, "%[^,],", list[i].nome);
        fscanf(file, "%[^,],", list[i].descricao);
        fscanf(file, "%[^,],", temp);
        list[i].cc.log = atof(temp);
        fscanf(file, "%[^,],", temp);
        list[i].cc.lat = atof(temp);
        fscanf(file, "%[^\n]\n", temp);
        n = atoi(temp);
        list->total = tam;
        ARRAY_POI * arr_poi = (ARRAY_POI *)malloc(sizeof(ARRAY_POI)*n);
        arr_poi->n_poi=n;
        for (int j = 0; j < n; ++j) {
            POI * poi = (POI *)malloc(sizeof(POI));
            fscanf(file, "%[^,],", nome_poi);
            fscanf(file, "%[^\n]\n", desc_poi);
            strcpy(poi->nome, nome_poi);
            strcpy(poi->descricao, desc_poi);
            arr_poi[j].p_poi = poi;
        }
        list[i].ar_poi = arr_poi;
    }
  fclose(file);
}

void read_file_cidade_bin(CIDADE *list){
    FILE *file = fopen("../cidade.txt","rb");
    int id = 0;
    char descricao[INFO];
    double latitude, longitude;
    if(file==NULL){
        printf("Error Failed to open file (bin)\n");
        exit(-1);
    }

    //Falta leitura do ficheiro em binario e loop

    fclose(file);
    //add_city(id, descricao, latitude, longitude, list);
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

void add_City(char *nome, char *descricao, float lat, float log){
    int n = list->total++;
    list = (CIDADE*)realloc(list, sizeof(CIDADE)*n);
    list[n].ar_poi = malloc(sizeof(ARRAY_POI));
    strcpy(list[n].nome,nome);
    strcpy(list[n].descricao,descricao);
    list[n].cc.lat = lat;
    list[n].cc.log = log;
    list[n].ar_poi->n_poi = 0;
    list[n].ar_poi->p_poi = NULL;
    printf("Cidade %s foi adicionada com sucesso\n", nome);
}

void print_city(){
    printf("%d\n\n",list->total);
    for (int i = 0; i < list->total; ++i) {
        printf("\nCidade : %s\n", list[i].nome);
        printf("Descricao : %s\n", list[i].descricao);
        printf("Latitude : %f\n", list[i].cc.lat);
        printf("Longitude : %f\n", list[i].cc.log);

        printf("Pontos de Interesse (%d)\n", list[i].ar_poi->n_poi);
        for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
            printf("\t %s \t ", list[i].ar_poi[j].p_poi->nome);
            printf("%s \n ", list[i].ar_poi[j].p_poi->descricao);
        }
    }
}
