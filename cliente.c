#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

#include "cliente.h"
#include "structs.h"
#include "cidade.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOME 50
#define MORADA 100
#define null NULL

CLIENTE_LISTA *client_list;

void cliente(int argc, const char *argv[]) {
    client_list = (CLIENTE_LISTA *)malloc(sizeof(CLIENTE_LISTA));
    client_list->phead = client_list->ptail = NULL; client_list->nclientes = 0;
    read_file_txt();
    //print_linked_user(list);

    //deleteClient(233434321,list);
    //deleteClient(321245675,list);
    //read_file_cliente_bin();
    printf("\n");
    //nif_order(list);
    print_linked_user(client_list);

    //write_file_client_txt(list, "../data/clientes_write.txt");
}

CLIENTE_LISTA *read_file_txt() {
    FILE *file;
    char line[MAX500], nome_cidade[MAX100], descricao[MAX100], nome_poi[MAX100], desc_poi[MAX100], name[MAX100], address[MAX100], temp[20];;
    int n_fiscal, contact, day, month, year, n;
    int tam, tem, tim;
    if ((file = fopen("../data/clientes.txt", "r")) == NULL) {
        printf("fopen clients.txt failed, exiting now...\n");
        exit(-1);
    }

    fscanf(file, "%d\n", &tam);
    for (int i = 0; i < tam; ++i) {
        CLIENTE *client = (CLIENTE *) malloc(sizeof(CLIENTE));
        fscanf(file, "%[^,],", client->nome);
        fscanf(file, "%[^,],", client->morada);
        fscanf(file, "%[^,],", temp);
        client->nif = atoi(temp);
        fscanf(file, "%[^,],", temp);
        client->contacto = atoi(temp);
        fscanf(file, "%[^,],", temp);
        client->nascimento.dia = atoi(temp);
        fscanf(file, "%[^,],", temp);
        client->nascimento.mes = atoi(temp);
        fscanf(file, "%[^,],", temp);
        client->nascimento.ano = atoi(temp);
        fscanf(file, "%[^\n]\n", temp);
        n = atoi(temp);
        client->historico_viagens.nviagens = n;
        VIAGEM *vg = (VIAGEM *)malloc(sizeof(VIAGEM) * n);
        for (int k = 0; k < n; ++k) {
            fscanf(file, "%d\n", &tem);
            vg->ncidades = tem;
            CIDADE * city = (CIDADE *)malloc(sizeof(CIDADE)*tem);
            for (int j = 0; j < tem; ++j) {

                fscanf(file, "%[^\n]\n", nome_cidade);
                city[j] = search_City(nome_cidade);
                vg[k].city = city;
            }
            client->historico_viagens.p_viagem = vg;
            if(n != 0) printf("%s\n", client->historico_viagens.p_viagem[k].city->nome);
        }

        add_client_to_head(client, client_list);
        //add_client_to_tail(client,list);
    }
    fclose(file);
}

void read_file_cliente_bin() {
    FILE *file;
    char name[NOME], address[MORADA];
    int n_fiscal, contact, day, month, year;
    if ((file = fopen("../clientes.bin", "rb")) == null) {
        printf("fopen clients.bin failed, exiting now...\n");
        exit(1);
    }


    //Falta leitura do ficheiro em binario e loop

    fclose(file);
}

CLIENTE * add_client(char *name, char *address, int n_fiscal, int contact, int day, int month, int year, CLIENTE_LISTA *list) {
    CLIENTE *client = (CLIENTE *) malloc(sizeof(CLIENTE));
    strcpy(client->nome, name);
    strcpy(client->morada, address);
    client->nif = n_fiscal;
    client->contacto = contact;
    client->nascimento.dia = day;
    client->nascimento.mes = month;
    client->nascimento.ano = year;
    client->pnext = null;
    //add_client_to_head(client, list);
    add_client_to_tail(client, list);
}

void add_client_to_tail(CLIENTE *client, CLIENTE_LISTA *list) {
    if (list->phead == NULL && list->nclientes == 0) { // Se não houver elementos inseridos na lista, insere o atual
        list->phead = client;
        list->ptail = client;
        list->nclientes++;
    } else {
        list->ptail->pnext = (struct client *) client;
        list->ptail = client;
        list->nclientes++;
    }
    list->ptail->pnext = null;
}

void add_client_to_head(CLIENTE *client, CLIENTE_LISTA *list) {
    if (list->phead == NULL && list->nclientes == 0) { // Se não houver elementos inseridos na lista, insere o atual
        list->phead = (CLIENTE *) client;
        list->ptail = (CLIENTE *) client;
        list->nclientes++;
    } else {
        client->pnext = (struct client *) list->phead;
        list->phead = client;
        list->nclientes++;
    }
    list->ptail->pnext = null;
}

CLIENTE_LISTA *deleteClient(int nif, CLIENTE_LISTA *list) {
    CLIENTE *remove;
    CLIENTE *cur = list->phead;
    while (cur != NULL) {
        if (cur->nif == nif) {
            list->phead = (CLIENTE *) cur->pnext;
            list->nclientes--;
            free(cur);
            printf("User has been deleted\n");
            return list;
        } else {
            while (cur->pnext != NULL) {
                remove = (CLIENTE *) cur->pnext;
                if (remove->nif == nif) {
                    if (remove->pnext == NULL) {
                        list->ptail = cur;
                        list->ptail->pnext = NULL;
                    } else cur->pnext = remove->pnext;
                    list->nclientes--;
                    free(remove);
                    printf("User has been deleted\n");
                    return list;
                } else cur = (CLIENTE *) cur->pnext;
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

void write_file_client_txt(CLIENTE_LISTA *list, char *path) {
    CLIENTE *temp = list->phead;
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("File for writing failed to open...");
        exit(-1);
    }
    for (int i = 0; i < list->nclientes; ++i) {
        fprintf(file, "%s,%s,%d,%d,%d,%d,%d\n", temp->nome, temp->morada, temp->nif, temp->contacto,
                temp->nascimento.dia, temp->nascimento.mes, temp->nascimento.ano);
        temp = (CLIENTE *) temp->pnext;
    }
}

void nif_order(CLIENTE_LISTA *list) {                                    //NOT WORKING
    CLIENTE_LISTA *new = (CLIENTE_LISTA *) malloc(sizeof(CLIENTE_LISTA));
    new->phead = new->ptail = NULL;
    new->nclientes = 0;
    CLIENTE *temp = list->phead;
    CLIENTE *temp1 = (CLIENTE *) temp->pnext;
    CLIENTE *aux;

    for (int i = 0; i < list->nclientes; ++i) {
        while (temp != NULL) {
            while (temp1 != NULL) {
                if (temp1->nif < temp->nif) {
                    aux = temp1;
                }
                temp1 = (CLIENTE *) temp1->pnext;
            }
            printf("%s\n", aux->nome);
            deleteClient(aux->nif, list);
            print_linked_user(list);
            temp = (CLIENTE *) temp->pnext;
        }
    }
}