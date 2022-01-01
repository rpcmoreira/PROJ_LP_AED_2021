#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOME 50
#define MORADA 100

int cliente(int argc, const char * argv[]){

}

void read_file_cliente_txt(){
    FILE *file;
    char name[NOME], address[MORADA];
    int n_fiscal, contact, day, month, year;
    if((file= fopen("../clientes.txt","r")) == NULL){
        printf("fopen clients.txt exiting now...\n");
        exit(-1);
    }
    fscanf(file, "%d", &n_fiscal);
    fscanf(file, "%d", &contact);
    fscanf(file, "%d", &day);
    fscanf(file, "%d", &month);
    fscanf(file, "%d", &year);
    fscanf(file, "%s", name);
    fscanf(file, "%s", address);
    add_cliente(nome, morada, nif, contacto, dia, mes, ano);
    fclose(file);
}

void read_file_cliente_bin(){
    FILE *file;
    char name[NOME], address[MORADA];
    int n_fiscal, contact, day, month, year;
    if((file= fopen("../clientes.bin","rb"))==NULL){
        printf("fopen clients.bin failed, exiting now...\n");
        exit(1);
    }
    fclose(file);
}

CLIENTE *add_client(char * name, char *address, int n_fiscal, int contact, int day, int month, int year){
    CLIENTE * client = (CLIENTE *)malloc(sizeof(CLIENTE));
    CLIENTE_LISTA * add
}
