/*
    * Lista Dinamicamente Encadeada

    * Arquivo: list.h
    * Descrição: Biblioteca com as funções do programa

    * Codigo por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programação II, Rafael Ballotin
    * Engenharia de Computação, 2016
*/

#include "struct.h"

//Inicia a lista, j� declara a proxima posi��o como NULL
void initialize (Products *products_list) {
    products_list->next_position = NULL;
}

//Verificar se a lista est� vazia ou n�o
int empty_list (Products *products_list) {
    if (products_list->next_position == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//fun��o recursiva para verificar se o c�digo ja existe
int check_list (int code, Products *products_list) {
    if(code == products_list->code){
        return 0;
    }else if(products_list->next_position == NULL){
        return 1;
    }else{
        check_list(code, products_list->next_position);
    }
}

//Inserir o item j� no come�o da lista
int insert_item (int *code, float *price, Products *products_list) {
    Products *new_product = (Products *) malloc(sizeof(Products));

    new_product->code = *code;
    new_product->price = *price;

    if (check_list(new_product->code, products_list)) {
        Products *last_product = products_list->next_position;
        products_list->next_position = new_product;
        new_product->next_position = last_product;
        return 1;
    } else {
        return NULL;
    }
}

//Liberar o espa�o na memoria
void clean_space (Products *products_list) {
    if (!empty_list(products_list)) { //Se a lista n�o estiver vazia
        Products *next, *current;

        current = products_list->next_position; //Pega a posi��o atual de memoria

        while (current != NULL) { //Enquanto n�o chegar na ultima posi��o
            next = current->next_position;
            free(current);
            current = next;
        }
    }
}

void save_itens (Products *products_list) {

    FILE *fp = fopen("products.dat", "w+b");

    Products *tmp = products_list->next_position;

    while (tmp != NULL) {

        fwrite(tmp, sizeof(Products), 1, fp);
        tmp = tmp->next_position;
    }

    fclose(fp);
}

//Na hora de fazer a inser��o do arquivo para o programa, ele vai fazer uma
//adi��o no final da lista, e n�o no inicio
void insert_item_from_stream (Products *products_list, Products *temp) {
    Products *new_product = (Products *) malloc(sizeof(Products));
    new_product->code = temp->code;
    new_product->price = temp->price;
    new_product->next_position = NULL;

    if (empty_list(products_list)) {
        products_list->next_position = new_product;
    } else {
        Products *tmp = products_list->next_position;

        while (tmp->next_position != NULL) {
            tmp = tmp->next_position;
        }

        tmp->next_position = new_product;
    }
}

void load_itens (Products *products_list) {
    FILE *fp = fopen("products.dat", "r+b");

    if (fp == NULL)
        fp = fopen("products.dat", "w+b");

    rewind(fp);

    Products *temp = malloc(sizeof(Products));

    while (fread(temp, sizeof(Products), 1, fp) != NULL) {
        insert_item_from_stream(products_list, temp);
    }

    free(temp);
    fclose(fp);
}

//fun��o recursiva para procurar o produto (n�o da erro quando n�o acha) ps: chupa adolpho
int search_list (int search_code, Products *s, Products *products_list) {
    if(search_code == products_list->code){
        s->code = products_list->code;
        s->price = products_list->price;
        return 1;
    }else if(products_list->next_position == NULL){
        return 0;
    }else{
        search_list(search_code, s, products_list->next_position);
    }
}

int remove_item (int x, Products *products_list) {
    Products *trash;
    Products *trashNext;
    if (!check_list(x, products_list)) {
        trash = products_list;
        trashNext = products_list->next_position;
        while (trashNext != NULL && trashNext->code != x) {
              trash = trashNext;
              trashNext = trashNext->next_position;
        }
        if (trashNext != NULL) {
              trash->next_position = trashNext->next_position;
              free(trashNext);
        }
        return 1;
    } else {
        return 0;
    }
}
