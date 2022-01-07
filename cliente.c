#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include "cliente.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOME 50
#define MORADA 100
#define null NULL

void cliente(int argc, const char * argv[]){
    CLIENTE_LISTA * list = (CLIENTE_LISTA *) malloc(sizeof(CLIENTE_LISTA));
    list->phead = list->ptail = null; list->nclientes = 0;
    read_file_cliente_txt(list);
    print_linked_user(list);
    deleteClient(197654234,list);
    print_linked_user(list);
    deleteClient(209543828,list);
    print_linked_user(list);
    //read_file_cliente_bin();

}

void read_file_cliente_txt(CLIENTE_LISTA *list) {
    FILE *file;
    char line[MAX500];
    char *name, *address;
    int n_fiscal, contact, day, month, year, n;
    if ((file = fopen("../data/clientes.txt", "r")) == NULL) {
        printf("fopen clients.txt failed, exiting now...\n");
        exit(-1);
    }
    while (fgets(line, sizeof(line), file) != null) {
        name = strtok(line, ",");
        address = strtok(null, ",");
        n_fiscal = atoi(strtok(null, ","));
        contact = atoi(strtok(null, ","));
        day = atoi(strtok(null, ","));
        month = atoi(strtok(null, ","));
        year = atoi(strtok(null, ""));
        add_client(name, address, n_fiscal, contact, day, month, year, list);
        //printf("%s %s %d %d %d %d %d", name, address, n_fiscal, contact, day, month, year);
    }
    fclose(file);
}

void read_file_cliente_bin(){
    FILE *file;
    char name[NOME], address[MORADA];
    int n_fiscal, contact, day, month, year;
    if((file= fopen("../clientes.bin","rb"))==null){
        printf("fopen clients.bin failed, exiting now...\n");
        exit(1);
    }


    //Falta leitura do ficheiro em binario e loop

    fclose(file);
}

CLIENTE *add_client(char * name, char *address, int n_fiscal, int contact, int day, int month, int year, CLIENTE_LISTA *list) {
    CLIENTE *client = (CLIENTE *) malloc(sizeof(CLIENTE));
    strcpy(client->nome, name);
    strcpy(client->morada, address);
    client->nif = n_fiscal;
    client->contacto = contact;
    client->nascimento.dia = day;
    client->nascimento.mes = month;
    client->nascimento.ano = year;
    client->pnext = null;
    add_client_to_head(client, list);
    //add_client_to_tail(client, list);
}

void add_client_to_tail(CLIENTE* client, CLIENTE_LISTA *list){
    if(list->phead==NULL && list->nclientes==0) { // Se não houver elementos inseridos na lista, insere o atual
        list->phead = client;
        list->ptail = client;
        list->nclientes++;
    }
    else{
        list->ptail->pnext = (struct client *) client;
        list->ptail = client;
        list->nclientes++;
    }
}

void add_client_to_head(CLIENTE *client, CLIENTE_LISTA *list){
    if(list->phead==NULL && list->nclientes==0) { // Se não houver elementos inseridos na lista, insere o atual
        list->phead = (CLIENTE *) client;
        list->ptail = (CLIENTE *) client;
        list->nclientes++;
    }
    else{
        client->pnext = (struct client *) list->phead;
        list->phead = client;
        list->nclientes++;
    }
}

CLIENTE_LISTA * deleteClient(int nif, CLIENTE_LISTA *list){
    CLIENTE * remove;
    CLIENTE * cur = list->phead;
    while(cur != null){
        if(cur->nif == nif){
            list->phead = (CLIENTE *) cur->pnext;
            list->nclientes--;
            free(cur);
            printf("User has been deleted\n");
            return list;
        }
        else{
            while(cur->pnext != null){
                remove = (CLIENTE *) cur->pnext;
                if(remove->nif == nif){
                    if(remove->pnext == null){
                        list->ptail = cur;
                        list->ptail->pnext = NULL;
                    }else cur->pnext = remove->pnext;
                    list->nclientes--;
                    free(remove);
                    printf("User has been deleted\n");
                    return list;
                }
            }

        }
    }
    printf("Delete Error, user non existent\n");
    return list;
}

void print_linked_user(CLIENTE_LISTA *head) {
    CLIENTE *print = head->phead;
    while (print != NULL) {
        printf("%s\t", print->nome);
        printf("%s\t", print->morada);
        printf("%d\t", print->nif);
        printf("%d\t", print->contacto);
        printf("%d\t", print->nascimento.dia);
        printf("%d\t", print->nascimento.mes);
        printf("%d\n", print->nascimento.ano);

        print = (CLIENTE *) print->pnext;
    }
}