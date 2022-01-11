#include "poi.h"
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
    //read_file_cliente_bin();

    search_nome_client("Eduardo Ferreira", client_list);
    //search_nif_client(233434321, client_list);

    //nif_order(client_list);
    //name_order(client_list);

    //add_client("Ana Moreira", "Rua das Verduras n.12", 199542361, 912345678, 27,7,2000, client_list);
    //deleteClient(197654234, client_list);                                                                 //Carla Dias

    //viagem_search("Eduardo Ferreira", client_list, "Coimbra");
    //poi_search("Eduardo Ferreira", client_list, "Portugal dos Pequenitos");


    //add_viagem(client_list, "Ana Moreira");
    //add_viagem(client_list, "Ana Moreira");
    //add_viagem(client_list, "Carla Dias");

    //delete_viagem(client_list, "Eduardo Ferreira");

    //edit_viagem(client_list, "Eduardo Ferreira",0, 2);

    edit_poi_Viagem(client_list, "Eduardo Ferreira", "Coimbra", "Portugal dos Pequeninos", 0, 1);
    search_nome_client("Eduardo Ferreira", client_list);
    edit_poi_Viagem(client_list, "Eduardo Ferreira", "Coimbra", "Portugal dos Pequeninos", 1, 0);
    search_nome_client("Eduardo Ferreira", client_list);
    //print_linked_user();

    //client_list = edit_city_Viagem(client_list, "Eduardo Ferreira", "Faro", 0, 0);
    //client_list = edit_city_Viagem(client_list, "Eduardo Ferreira", "Lisboa", 0, 0);
    //client_list = edit_city_Viagem(client_list, "Eduardo Ferreira", "Porto", 0, 0);
    //client_list = edit_city_Viagem(client_list, "Eduardo Ferreira", "Coimbra", 0, 2);

    //search_City("Barcelos");
    //generate_Rel("Ana Moreira");
    //print_linked_user();

    write_file_client_txt();
    write_file_cliente_bin();
}

void read_file_txt() {
    FILE *file;
    char nome_cidade[MAX100], nome_poi[MAX100],temp[20];
    int tam, tem,n, n_poi = 0;
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
                fscanf(file, "%[^,],", nome_cidade);
                city[j] = search_City(nome_cidade);
                fscanf(file, "%[^\n]\n", temp);
                n_poi = atoi(temp);
                ARRAY_POI * arr_poi = (ARRAY_POI *)malloc(sizeof(ARRAY_POI));
                arr_poi->p_poi = n_poi;
                POI * poi = (POI *)malloc(sizeof(POI)*n_poi);
                for (int j = 0; j < n_poi; ++j) {
                    fscanf(file, "%[^\n]\n", nome_poi);
                    poi[j] = search_Poi(nome_poi, nome_cidade);
                    arr_poi->p_poi = poi;
                }

                city[j].ar_poi = arr_poi;
                vg[k].city = city;
            }
            client->historico_viagens.p_viagem = vg;
        }

        //add_client_to_head(client, client_list);
        add_client_to_tail(client, client_list);
    }
    fclose(file);
}

void write_file_client_txt() {
    CLIENTE *temp = client_list->phead;
    FILE *file = fopen("../data/clientes_write.txt", "w");
    if (file == NULL) {
        printf("File for writing failed to open...");
        exit(-1);
    }
    fprintf(file, "%d\n",client_list->nclientes);
    while (temp != null){
        fprintf(file, "%s,%s,%d,%d,%d,%d,%d,%d\n", temp->nome, temp->morada, temp->nif, temp->contacto, temp->nascimento.dia, temp->nascimento.mes, temp->nascimento.ano, temp->historico_viagens.nviagens);
        for (int i = 0; i < temp->historico_viagens.nviagens; ++i) {
            fprintf(file, "%d\n", temp->historico_viagens.p_viagem[i].ncidades);
            for (int j = 0; j < temp->historico_viagens.p_viagem[i].ncidades; ++j) {
                fprintf(file, "%s,%d\n", temp->historico_viagens.p_viagem[i].city[j].nome, temp->historico_viagens.p_viagem[i].city[j].ar_poi->n_poi);
                for (int k = 0; k < temp->historico_viagens.p_viagem[i].city[j].ar_poi->n_poi; ++k) {
                    fprintf(file, "%s\n", temp->historico_viagens.p_viagem[i].city[j].ar_poi->p_poi[k].nome);
                }
            }
        }
        temp = (CLIENTE *) temp->pnext;
    }
    printf("Cliente_txt is finished\n");
    fclose(file);
}

void read_file_cliente_bin() {
    FILE *file;
    if ((file = fopen("../data/clientes.bin", "rb")) == null) {
        printf("fopen clients.bin failed, exiting now...\n");
        exit(1);
    }
    char nome[MAX100], morada[MAX250], cidade[MAX100], desc[MAX250];
    int cont, nif, n_viagens, n_cidades, n_clientes,dia,mes,ano;

    fread(&n_clientes, sizeof(int), 1, file);
    for (int i = 0; i < n_clientes; ++i) {
        CLIENTE *client = (CLIENTE *) malloc(sizeof(CLIENTE));
        fread(&nome, sizeof(strlen(nome)), 1, file);
        fread(&morada, sizeof(strlen(morada)), 1, file);
        fread(&nif, sizeof(int), 1, file);
        fread(&cont, sizeof(int), 1, file);
        fread(&n_viagens, sizeof(int), 1, file);
        fread(&dia, sizeof(int), 1, file);
        fread(&mes, sizeof(int), 1, file);
        fread(&ano, sizeof(int), 1, file);

        strcpy(client->nome, nome);
        strcpy(client->morada, morada);
        client->nif = nif;
        client->contacto = cont;
        client->nascimento.dia = dia;
        client->nascimento.mes = mes;
        client->nascimento.ano = ano;
        client->historico_viagens.nviagens = n_viagens;

        VIAGEM *vg = (VIAGEM *)malloc(sizeof(VIAGEM) * n_viagens);
        for (int j = 0; j < n_viagens; ++j) {
            fread(&n_cidades, sizeof(int), 1, file);
            CIDADE * city = (CIDADE *)malloc(sizeof(CIDADE)*n_cidades);
            for (int k = 0; k < n_cidades; ++k) {
                fread(&cidade, sizeof(strlen(cidade)), 1, file);
                city[j] = search_City(cidade);
                vg[j].city = city;
            }
            client->historico_viagens.p_viagem = vg;
        }
        add_client_to_tail(client, client_list);
    }
    printf("Cidade_bin is finished\n");
    fclose(file);
}

void write_file_cliente_bin() {
    CLIENTE * cliente = client_list->phead;
    FILE *file;
    if ((file = fopen("../data/clientes.bin", "wb")) == null) {
        printf("fopen clients.bin failed, exiting now...\n");
        exit(1);
    }
    fwrite(&client_list->nclientes, sizeof(int), 1, file);
    while (cliente != null){
        char nome[MAX100], morada[MAX250], cidade[MAX100], desc[MAX250];
        int cont, nif, n_viagens, n_cidades, dia, mes, ano;

        strcpy(nome, cliente->nome);
        strcpy(nome, cliente->nome);
        cont = cliente->contacto;
        nif = cliente->nif;
        n_viagens = cliente->historico_viagens.nviagens;
        dia = cliente->nascimento.dia;
        mes = cliente->nascimento.mes;
        ano = cliente->nascimento.ano;


        fwrite(&nome, sizeof(strlen(nome)+1), 1, file);
        fwrite(&morada, sizeof(strlen(morada)+1), 1, file);
        fwrite(&nif, sizeof(int), 1, file);
        fwrite(&cont, sizeof(int), 1, file);
        fwrite(&dia, sizeof(int), 1, file);
        fwrite(&mes, sizeof(int), 1, file);
        fwrite(&ano, sizeof(int), 1, file);

        fwrite(&n_viagens, sizeof(int), 1, file);
        for (int i = 0; i < cliente->historico_viagens.nviagens; ++i) {
            n_cidades = cliente->historico_viagens.p_viagem[i].ncidades;

            fwrite(&n_cidades, sizeof(int), 1, file);
            for (int j = 0; j < cliente->historico_viagens.p_viagem[i].ncidades; ++j) {
                strcpy(cidade, cliente->historico_viagens.p_viagem[i].city[j].nome);
                strcpy(desc, cliente->historico_viagens.p_viagem[i].city[j].descricao);

                fwrite(&cidade, sizeof(strlen(cidade)+1), 1, file);
                fwrite(&desc, sizeof(strlen(desc)+1), 1, file);
            }
        }
        cliente = (CLIENTE *) cliente->pnext;
    }
    printf("Cidade_bin is finished\n");
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
                    printf("%s has been deleted\n", remove->nome);
                    free(remove);
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
                VIAGEM vg = teste->historico_viagens.p_viagem[i];
                printf("%d\n", vg.ncidades);
                for (int j = 0; j < vg.ncidades; ++j) {
                    printf("%s\n", vg.city[j].nome);
                }
                printf("\n");
            }

        printf("\n");
        teste = (CLIENTE *) teste->pnext;
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
                VIAGEM vg = client->historico_viagens.p_viagem[i];
                for (int j = 0; j < vg.ncidades; ++j) {
                    printf("%s\n", vg.city[j].nome);
                    for (int k = 0; k < vg.city[j].ar_poi->n_poi; ++k) {
                        printf("%s\n", vg.city[j].ar_poi->p_poi[k].nome);
                    }
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
            for (int i = 0; i < client->historico_viagens.nviagens; ++i) {
                VIAGEM vg = client->historico_viagens.p_viagem[i];
                for (int j = 0; j < vg.ncidades; ++j) {
                    printf("%s\n", vg.city[j].nome);
                }
                printf("\n");
            }
            break;
        }
        printf("\n");
        client = (CLIENTE *) client->pnext;
    }
}

void viagem_search(char *nome, CLIENTE_LISTA *lista, char  *cidade){
    CLIENTE *client;
    client = lista->phead;
    while(client != null){
        if(strcmp(nome, client->nome) == 0){
            if(client->historico_viagens.nviagens == 0){
                printf("Error, user doesnt have trips\n");
                return;
            }
            for (int i = 0; i < client->historico_viagens.nviagens; ++i) {
                for (int j = 0; j < client->historico_viagens.p_viagem[j].ncidades; ++j) {
                    if(strcmp(client->historico_viagens.p_viagem[i].city[j].nome,cidade) == 0){
                        printf("%s passou por %s na viagem %d\n", nome, cidade, i);
                    }
                }
            }
            return;
        }
        client = (CLIENTE *) client->pnext;
    }
}

void poi_search(char *nome, CLIENTE_LISTA *lista, char  *poi){
    CLIENTE *client;
    client = lista->phead;
    while(client != null){
        if(strcmp(nome, client->nome) == 0){
            if(client->historico_viagens.nviagens == 0){
                printf("Error, user doesnt have trips\n");
                return;
            }
            for (int i = 0; i < client->historico_viagens.nviagens; ++i) {
                for (int j = 0; j < client->historico_viagens.p_viagem[i].ncidades; ++j) {
                    for (int k = 0; k < client->historico_viagens.p_viagem[i].city[j].ar_poi->n_poi; ++k) {
                        if(strcmp(poi, client->historico_viagens.p_viagem[i].city[j].ar_poi->p_poi[k].nome) == 0){
                            printf("%s visitou %s na viagem %d\n", client->nome, poi, i);
                        }
                    }
                }
            }
            return;
        }
        client = (CLIENTE *) client->pnext;
    }
}

void generate_Rel(char *nome){
    CLIENTE *c = client_list->phead;
    while(c != null){
        if(strcmp(c->nome, nome) == 0){
            char filename[64];
            sprintf (filename, "../data/%s.txt", c->nome);
            FILE *file = fopen(filename, "w");
            if(file == NULL){
                printf("Rel open error\n");
                exit(-1);
            }
            fprintf(file, "The Person's name is %s and he/she was born in %d/%d/%d\n", c->nome, c->nascimento.dia, c->nascimento.mes, c->nascimento.ano);
            fprintf(file, "The Person lives in %s\n", c->morada);
            fprintf(file, "The Person has %d trips made\n\n", c->historico_viagens.nviagens);
            for (int i = 0; i < c->historico_viagens.nviagens; ++i) {
                fprintf(file, "\tTrip %d\n", i+1);
                fprintf(file, "\tThe Person visited: ");
                for (int j = 0; j < c->historico_viagens.p_viagem[i].ncidades; ++j) {
                    fprintf(file, "\t\t%s ", c->historico_viagens.p_viagem[i].city[j].nome);
                }
            }

            fclose(file);
            return;
        }
        c = (CLIENTE *) c->pnext;
    }
    printf("Person Not Found\n");
}