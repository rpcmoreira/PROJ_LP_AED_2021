#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOME 50
#define MORADA 100

int cliente(int argc, const char * argv[]){
    read_file_cliente_txt();
    //read_file_cliente_bin();

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
    add_client_head(name, address, n_fiscal, contact, day, month, year);
    //add_client_tail(name, address, n_fiscal, contact, day, month, year);
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

CLIENTE *add_client_head(char * name, char *address, int n_fiscal, int contact, int day, int month, int year){
    CLIENTE * client = (CLIENTE *)malloc(sizeof(CLIENTE));
    CLIENTE_LISTA * add;
    add = (CLIENTE_LISTA *)realloc((int*)add->nclientes, add->nclientes*sizeof(CLIENTE));
    DATA nascimento;
    strcpy(client->nome, name);
    strcpy(client->morada, address);
    client->nif = n_fiscal;
    client->contacto = contact;
    client->nascimento.dia=day;
    client->nascimento.mes=month;
    client->nascimento.ano=year;

    add_to_tail(client, add);
    add_to_head(client, add);
    return client;
}

CLIENTE *add_client_tail(char * name, char *address, int n_fiscal, int contact, int day, int month, int year) {
    CLIENTE *client = (CLIENTE *) malloc(sizeof(CLIENTE));
    CLIENTE_LISTA *add;
    add = (CLIENTE_LISTA *) realloc((int *) add->nclientes, add->nclientes * sizeof(CLIENTE));
    DATA nascimento;
    strcpy(client->nome, name);
    strcpy(client->morada, address);
    client->nif = n_fiscal;
    client->contacto = contact;
    client->nascimento.dia = day;
    client->nascimento.mes = month;
    client->nascimento.ano = year;

    add_to_tail(client, add);
}

void add_to_tail(CLIENTE *client, CLIENTE_LISTA *list){
    if(list->phead==NULL && list->nclientes==0) { // Se não houver elementos inseridos na lista, insere o atual
        list = (CLIENTE_LISTA *) malloc(sizeof(CLIENTE_LISTA));
        list->phead = (CLIENTE *) cliente;
        list->ptail = (CLIENTE *) cliente;
        client->pnext = NULL;
    }
    else{
        list->ptail = client;
        client->pnext = NULL;
    }
}

void add_to_head(CLIENTE *client, CLIENTE_LISTA *list){
    if(list->phead==NULL && list->nclientes==0) { // Se não houver elementos inseridos na lista, insere o atual
        list = (CLIENTE_LISTA *) malloc(sizeof(CLIENTE_LISTA));
        list->phead = (CLIENTE *) cliente;
        list->ptail = (CLIENTE *) cliente;
        client->pnext = NULL;
    }
    else{
        client->pnext = (struct client *) list->phead;
        list->phead = client;
    }
}

CLIENTE_LISTA * deleteClient(int nif){
    CLIENTE_LISTA *deleteUser;
    CLIENTE * remove;
    CLIENTE * temp;
    int aux = 0;
    for (aux; aux < deleteUser->nclientes; ++aux) {
        if(remove->nif == nif){
            temp = remove;
            remove->pnext = temp->pnext;
            free(temp);
            deleteUser->nclientes--;
            printf("The user was removed without any issue\n");
            break;
        }
        else{
            remove = (CLIENTE *) remove->pnext;
        }
    }
    printf("User not found\n");
    return deleteUser;
}