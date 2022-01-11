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

    add_City("Lamego", "Cidade de Lamego", 43.32f, 21.12f);

    edit_cidade(list, 42.42f, 42.42f, "Esta e a cidade de lisboa, onde o benfica joga", "Lisboa", 0);
    edit_cidade(list, 42.42f, 42.42f, "Esta e a cidade de lisboa, onde o benfica joga", "Lisboa", 1);

    add_poi(list, "Lamego", "Castelo de Lamego", "Castelo da Cidade de Lamego");
    add_poi(list, "Lamego", "Capela Nossa Senhora dos Remedios", "Capela da nossa Senhora dos Remedios");
    add_poi(list, "Porto", "Rotunda Boavista", "Rotunda enorme perto do centro do Porto");
    delete_poi(list, "Lisboa", "Oceanario de Lisboa");

    search_poi(list, "Estadio do Dragao");
    search_poi_cidade(list, "Lisboa");

    print_all_city();

    print_city("Barcelos");
    write_file_cidade_txt();

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
        ARRAY_POI * arr_poi = (ARRAY_POI *)malloc(sizeof(ARRAY_POI));
        arr_poi->n_poi=n;
        POI * poi = (POI *)malloc(sizeof(POI)*n);
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%[^,],", nome_poi);
            fscanf(file, "%[^\n]\n", desc_poi);
            strcpy(poi[j].nome, nome_poi);
            strcpy(poi[j].descricao, desc_poi);
            arr_poi->p_poi = poi;
        }

        list[i].ar_poi = arr_poi;

    }
    fclose(file);
}

void read_file_cidade_bin(){

    FILE *file = fopen("../cidade.txt","rb");

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
    int n = list->total;
    list = realloc(list, sizeof(CIDADE)*(n+1));
    list[n].ar_poi = malloc(sizeof(ARRAY_POI));
    strcpy(list[n].nome,nome);
    strcpy(list[n].descricao,descricao);
    list[n].cc.lat = lat;
    list[n].cc.log = log;
    list[n].ar_poi->n_poi = 0;
    list[n].ar_poi->p_poi = NULL;
    list->total++;
    printf("Cidade %s foi adicionada com sucesso\n", nome);
}

void print_all_city(){
    for (int i = 0; i < list->total; ++i) {
        printf("\n\nCidade : %s\n", list[i].nome);
        printf("Descricao : %s\n", list[i].descricao);
        printf("Latitude : %f\n", list[i].cc.lat);
        printf("Longitude : %f\n", list[i].cc.log);

        printf("Pontos de Interesse (%d)\n", list[i].ar_poi->n_poi);
        for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
            printf("\t %s \t ", list[i].ar_poi->p_poi[j].nome);
            printf("%s \n ", list[i].ar_poi->p_poi[j].descricao);
        }
    }
}

void print_city(char *city){
    for (int i = 0; i < list->total; ++i) {
        if(strcmp(city, list[i].nome) == 0) {
            printf("\n\nCidade %s Encontrada\n", list[i].nome);
            printf("Descricao : %s\n", list[i].descricao);
            printf("Latitude : %f\n", list[i].cc.lat);
            printf("Longitude : %f\n", list[i].cc.log);

            printf("Pontos de Interesse (%d)\n", list[i].ar_poi->n_poi);
            for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
                printf("\t %s \t ", list[i].ar_poi->p_poi[j].nome);
                printf("%s \n ", list[i].ar_poi->p_poi[j].descricao);
            }
            return;
        }
    }
    printf("\n%s doesnt not exist or it wasn't created\n", city);
}

void edit_cidade(CIDADE * city, float lat, float log, char *desc, char *cidade, int type){
    for (int i = 0; i < city->total; ++i) {
        if(strcmp(city[i].nome, cidade) == 0){
            switch (type) {
                case 0:
                    strcpy(city[i].descricao, desc);
                    return;

                case 1:
                    city[i].cc.log = log;
                    city[i].cc.lat = lat;
                    return;

                default: printf("Error in city_edit"); return;
            }
        }
    }
}

void write_file_cidade_txt(){
    FILE *file;
    if ((file = fopen("../data/cidade_write.txt", "w")) == NULL) {
        printf("fopen cidade.txt failed, exiting now...\n");
        exit(-1);
    }
    fprintf(file, "%d\n", list->total);
    for (int i = 0; i < list->total; ++i) {
        fprintf(file,"%s,%s,%f,%f,%d\n",list[i].nome,list[i].descricao,list[i].cc.log,list[i].cc.lat,list[i].ar_poi->n_poi);
        for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
            fprintf(file, "%s,%s\n",list[i].ar_poi->p_poi[j].nome,list[i].ar_poi->p_poi[j].descricao);
        }
    }
    printf("Cidade_write is finished\n");
    fclose(file);
}
