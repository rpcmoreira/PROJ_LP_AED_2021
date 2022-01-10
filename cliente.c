#include "poi.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"
#include "structs.h"
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
    printf("\n");

    //print_linked_user();

    //search_nome_client("Eduardo Ferreira", client_list);
    //search_nif_client(209543828, client_list);

    //nif_order(client_list);
    //name_order(client_list);

    add_client("Ana Moreira", "Rua das Verduras n.12", 199542361, 912345678, 27,7,2000, client_list);
    //deleteClient(197654234, client_list);      //Carla Dias

    //add_viagem(client_list, "Ana Moreira");
    //add_viagem(client_list, "Carla Dias");

    //delete_viagem(client_list, "Eduardo Ferreira");

    //client_list = edit_city_Viagem(client_list, "Eduardo Ferreira", "Faro", 1, 1);

    //edit_viagem(client_list, "Eduardo Ferreira",0, 2);

    printf("\n");

    //print_linked_user();

    //write_file_client_txt(list, "../data/clientes_write.txt");
}

CLIENTE_LISTA *read_file_txt() {
    FILE *file;
    char nome_cidade[MAX100],temp[20];
    int tam, tem,n;
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
            vg[k].ncidades = tem;
            CIDADE * city = (CIDADE *)malloc(sizeof(CIDADE)*tem);
            for (int j = 0; j < tem; ++j) {
                fscanf(file, "%[^\n]\n", nome_cidade);
                city[j] = search_City(nome_cidade);
                vg[k].city = city;
            }
            client->historico_viagens.p_viagem = vg;
        }

        //add_client_to_head(client, client_list);
        add_client_to_tail(client, client_list);
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
    client->historico_viagens.nviagens = 0;
    client->historico_viagens.p_viagem = NULL;
    client->pnext = null;
    //add_client_to_head(client, list);
    add_client_to_tail(client, list);

    //nif_order(client_list);
    //name_order(client_list);
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

void print_linked_user() {
    CLIENTE *teste = client_list->phead;
    while(teste != null){
            printf("\nUser Encontrado : %s\n", teste->nome);
            printf("Morada : %s\n", teste->morada);
            printf("NIF : %d\n", teste->nif);
            printf("Contacto : %d\n", teste->contacto);
            printf("Data : %d/%d/%d\n", teste->nascimento.dia, teste->nascimento.mes, teste->nascimento.ano);
            printf("Realizou %d viagens\n", teste->historico_viagens.nviagens);
            for (int i = 0; i < teste->historico_viagens.nviagens; ++i) {
                VIAGEM *vg = teste->historico_viagens.p_viagem;
                printf("%d\n", vg[i].ncidades);
                for (int j = 0; j < vg[i].ncidades; ++j) {
                    printf("%s\n", vg[i].city[j].nome);
                }
                printf("\n");
            }

        printf("\n");
        teste = (CLIENTE *) teste->pnext;
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

void nif_order(CLIENTE_LISTA *list) {
    CLIENTE *current = (CLIENTE *) list->phead, *index = NULL;
    CLIENTE *temp = (CLIENTE *)malloc(sizeof(CLIENTE));

    if(list->phead == NULL) {
        return;
    }
    else {
        while(current != NULL) {
            index = (CLIENTE *) current->pnext;

            while(index != NULL) {
                if(current->nif > index->nif) {
                    strcpy(temp->nome, current->nome);
                    strcpy(temp->morada, current->morada);
                    temp->nif = current->nif;
                    temp->contacto = current->contacto;
                    temp->nascimento.dia = current->nascimento.dia;
                    temp->nascimento.mes = current->nascimento.mes;
                    temp->nascimento.ano = current->nascimento.ano;
                    temp->historico_viagens = current->historico_viagens;

                    strcpy(current->nome, index->nome);
                    strcpy(current->morada, index->morada);
                    current->nif = index->nif;
                    current->contacto = index->contacto;
                    current->nascimento.dia = index->nascimento.dia;
                    current->nascimento.mes = index->nascimento.mes;
                    current->nascimento.ano = index->nascimento.ano;
                    current->historico_viagens = index->historico_viagens;

                    strcpy(index->nome, temp->nome);
                    strcpy(index->morada, temp->morada);
                    index->nif = temp->nif;
                    index->contacto = temp->contacto;
                    index->nascimento.dia = temp->nascimento.dia;
                    index->nascimento.mes = temp->nascimento.mes;
                    index->nascimento.ano = temp->nascimento.ano;
                    index->historico_viagens = temp->historico_viagens;
                }
                index = (CLIENTE *) index->pnext;
            }
            current = (CLIENTE *) current->pnext;
        }
    }
}

void name_order(CLIENTE_LISTA *list){
    CLIENTE *current = (CLIENTE *) list->phead, *index = NULL;
    CLIENTE *temp = (CLIENTE *)malloc(sizeof(CLIENTE));

    if(list->phead == NULL) {
        return;
    }
    else {
        while(current != NULL) {
            index = (CLIENTE *) current->pnext;

            while(index != NULL) {
                if(strcmp(index->nome, current->nome)) {
                    strcpy(temp->nome, current->nome);
                    strcpy(temp->morada, current->morada);
                    temp->nif = current->nif;
                    temp->contacto = current->contacto;
                    temp->nascimento = current->nascimento;
                    temp->historico_viagens = current->historico_viagens;

                    strcpy(current->nome, index->nome);
                    strcpy(current->morada, index->morada);
                    current->nif = index->nif;
                    current->contacto = index->contacto;
                    current->nascimento = index->nascimento;
                    current->historico_viagens = index->historico_viagens;

                    strcpy(index->nome, temp->nome);
                    strcpy(index->morada, temp->morada);
                    index->nif = temp->nif;
                    index->contacto = temp->contacto;
                    index->nascimento = temp->nascimento;
                    index->historico_viagens = temp->historico_viagens;
                }
                index = (CLIENTE *) index->pnext;
            }
            current = (CLIENTE *) current->pnext;
        }
    }
}

void search_nome_client(char *nome, CLIENTE_LISTA * lista){
    CLIENTE *client;
    client = lista->phead;
    while(client != null){
        if(strcmp(nome, client->nome) == 0){
            printf("\nUser Encontrado : %s\n", nome);
            printf("Morada : %s\n", client->morada);
            printf("NIF : %d\n", client->nif);
            printf("Contacto : %d\n", client->contacto);
            printf("Data : %d/%d/%d\n", client->nascimento.dia, client->nascimento.mes, client->nascimento.ano);
            printf("Realizou %d viagens\n", client->historico_viagens.nviagens);
            for (int i = 0; i < client->historico_viagens.nviagens; ++i) {
                VIAGEM *vg = client->historico_viagens.p_viagem;
                for (int j = 0; j < vg[i].ncidades; ++j) {
                    printf("%s\n", vg[i].city[j].nome);
                }
                printf("\n");
            }
            break;
        }
        printf("\n");
        client = (CLIENTE *) client->pnext;
    }
}

void search_nif_client(int nif, CLIENTE_LISTA * lista){
    CLIENTE *client = lista->phead;
    while(client != null){
        if(nif == client->nif){
            printf("\nUser Encontrado : %s\n", client->nome);
            printf("Morada : %s\n", client->morada);
            printf("NIF : %d\n", client->nif);
            printf("Contacto : %d\n", client->contacto);
            printf("Data : %d/%d/%d\n", client->nascimento.dia, client->nascimento.mes, client->nascimento.ano);
            printf("Realizou %d viagens\n", client->historico_viagens.nviagens);
          break;
        }
        client = (CLIENTE *) client->pnext;
    }
}