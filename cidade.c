#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ag.h"
#define null NULL

#define INFO 258

CIDADE * list;

void cidade(int argc, const char * argv[]){
    list = (CIDADE *)malloc(sizeof(CIDADE));
    list->total = 0;
    read_file_cidade_txt();

    //ag(list);


    //add_City("Lamego", "Cidade de Lamego", 43.32f, 21.12f);
    add_City("Barcelos", "Casa do Gil Vicente e do galo de Barcelos", 20.22f, 20.22f);

    //edit_cidade(list, 42.42f, 42.42f, "Esta e a cidade de lisboa, onde o benfica joga", "Lisboa", 0); //0 descricao, 1 lat/log
    //edit_cidade(list, 42.42f, 42.42f, "Esta e a cidade de lisboa, onde o benfica joga", "Lisboa", 1);

    //add_poi(list, "Lamego", "Castelo de Lamego", "Castelo da Cidade de Lamego");
    //add_poi(list, "Lamego", "Capela Nossa Senhora dos Remedios", "Capela da nossa Senhora dos Remedios");
    //add_poi(list, "Barcelos", "Galo de Barcelos", "Galo mais famoso de Portugal");
    //add_poi(list, "Porto", "Rotunda Boavista", "Rotunda enorme perto do centro do Porto");

    //delete_poi(list, "Lisboa", "Oceanario de Lisboa");
    //delete_poi(list, "Lisboa", "Parque das Nacoes");

    //search_poi(list, "Estadio do Dragao");
    //search_poi(list, "Oceanario de Lisboa");
    //search_poi_cidade(list, "Lisboa");

    //print_all_city();
    //print_city("Barcelos");

    //binarySearchCidades(list, "Coimbra");
    //list = insertionSort(list);
    //binarySearchCidades(list, "Coimbra");

    write_file_cidade_txt();
    //write_file_cidade_bin();
}
/**
 * Leitura das Cidades em txt
 */
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

/**
 * Escrever para um txt as cidades
 */
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

/**
 * Ler de bin files
 */
void read_file_cidade_bin(){

    FILE *file = fopen("../cidade.txt","rb");

    if(file==NULL){
        printf("Error Failed to open file (bin)\n");
        exit(-1);
    }

    char nome[MAX100], desc[MAX500], p_nome[MAX100], p_desc[MAX250];
    int n_poi, n_cidades;
    double lat, log;

    fread(&n_cidades, sizeof(int), 1, file);
    list = realloc(list, sizeof(CIDADE) * n_cidades);
    for (int i = 0; i < n_cidades; ++i) {
        fread(&nome, sizeof(strlen(nome)), 1, file);
        fread(&desc, sizeof(strlen(desc)), 1, file);
        fread(&lat, sizeof(double), 1, file);
        fread(&log, sizeof(double), 1, file);
        fread(&n_poi, sizeof(int), 1, file);

        strcpy(list[i].nome, nome);
        strcpy(list[i].descricao, desc);
        list[i].cc.lat = lat;
        list[i].cc.log = log;
        list[i].ar_poi->n_poi = n_poi;
        list[i].ar_poi->p_poi = realloc(list[i].ar_poi->p_poi, sizeof(POI)*n_poi);
        for (int j = 0; j < n_poi; ++j){
            fread(&p_nome, sizeof(strlen(p_nome)), 1, file);
            fread(&p_desc, sizeof(strlen(p_desc)), 1, file);
            strcpy(list[i].ar_poi->p_poi[j].nome, nome);
            strcpy(list[i].ar_poi->p_poi[j].descricao, desc);
        }
        fclose(file);
    }
}

/**
 * Escrever para ficheiro bin as cidades
 */
void write_file_cidade_bin(){
    FILE *file;
    char nome_poi[MAX100], desc_poi[MAX100];
    char temp[20];
    int n, tam;
    if ((file = fopen("../data/cidade.bin", "wb")) == NULL) {
        printf("fopen cidade.bin failed, exiting now...\n");
        exit(-1);
    }
    fwrite(&list->total, sizeof(int), 1, file);
    for (int i = 0; i < list->total; ++i) {
        fwrite(list[i].nome, sizeof(strlen(list[i].nome)+1), 1, file);
        fwrite(list[i].descricao, sizeof(strlen(list[i].descricao)+1), 1, file);
        fwrite(&list[i].cc.log, sizeof(float), 1, file);
        fwrite(&list[i].cc.lat, sizeof(float), 1, file);
        fwrite(&list[i].ar_poi->n_poi, sizeof(int), 1, file);
        for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
            fwrite(list[i].ar_poi->p_poi[j].nome, sizeof(strlen(list[i].ar_poi->p_poi[j].nome)+1),1, file);
            fwrite(list[i].ar_poi->p_poi[j].descricao, sizeof(strlen(list[i].ar_poi->p_poi[j].descricao)+1),1, file);
        }
    }
    fclose(file);
}


/**
 * Procura uma cidade pelo nome e devolve a sua informacao
 * @param name - nome da cidade a procurar
 * @return
 */
CIDADE search_City(char *name){
    for (int i = 0; i < list->total; ++i) {
        if(strcmp(list[i].nome, name) == 0){
            return list[i];
        }
    }
    printf("Nao encontrei cidade...\n");
    exit(-1);
}

/**
 * Procura um poi numa cidade e devolve a sua info
 * @param poi - ponto a procurar
 * @param cidade - cidade onde se quer procurar
 * @return
 */
POI search_Poi(char *poi, char *cidade){
    for (int i = 0; i < list->total; ++i) {
        if(strcmp(list[i].nome, cidade) == 0){
            for (int j = 0; j < list[i].ar_poi->n_poi; ++j) {
                if(strcmp(poi, list[i].ar_poi->p_poi[j].nome) == 0)
                    return list[i].ar_poi->p_poi[j];
            }
        }
    }
}

/**
 * adiciona a cidade ao array dinamico das cidades
 * @param nome - nome da cidade
 * @param descricao - descricao da cidade
 * @param lat - latitude
 * @param log - longitude
 */
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

/**
 * imprime todas as cidades e os seus POIS
 */
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

/**
 * imprime uma cidade especifica
 * @param city - nome da cidade a imprimir
 */
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

/**
 * Edita informacoes da cidade
 * @param city - array cidades
 * @param lat - latitude
 * @param log - longitude
 * @param desc - descricao da cidade
 * @param cidade - nome da cidade a alterar
 * @param type - modo de edicao
 */
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


/**
 * Aplica um binary search de forma a encontrar a cidade
 * @param cidade - lista de cidades
 * @param nome - nome da cidade a procurar
 */
void binarySearchCidades(CIDADE *cidade, char *nome){
    int low = 0;
    int high = cidade->total - 1;
    while(low <= high){
        int mid = (low+high)/2;

        if(strcmp(nome, cidade[mid].nome) < 0){
            high = mid - 1;
        }
        else if(strcmp(nome, cidade[mid].nome) > 0){
            low = mid + 1;
        }
        else if(strcmp(nome, cidade[mid].nome) == 0){
            printf("Found city at position %d", mid);
            print_city(nome);
            break;
        }
        else{
            printf("City not found!\n");
        }
    }
}

/**
 * Reorganiza o array de forma alfabetica usando insertionSort
 * @param cidade - Array Cidades
 * @return
 */
CIDADE * insertionSort(CIDADE *cidade){
    int i, j;
    int p = cidade->total;
    CIDADE key;
    for (i = 1; i < p; i++) {
        key = cidade[i];
        j = i - 1;

        while (j >= 0 && strcmp(cidade[j].nome, key.nome) > 0) {
            cidade[j + 1] = cidade[j];
            j = j - 1;
        }
        cidade[j + 1] = key;
    }

    cidade->total = p;
    return cidade;
}

