/*
    * Lista Dinamicamente Encadeada

    * Arquivo: main.c
    * Descrição: Estrutura principal do programa

    * Codigo por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programação II, Rafael Ballotin
    * Engenharia de Computação, 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main () {

    Products *products_list = (Products *) malloc(sizeof(Products));
    initialize(products_list);
    load_itens(products_list);

    int code, choice, x;
    float price;

    do {
        system("clear");
        printf(" 1 - SHOW LIST\n 2 - ADD PRODUCT\n 3 - SEARCH PRODUCT\n 4 - REMOVE PRODUCT\n 0 - EXIT \n-->");
        scanf(" %d", &choice);

        switch (choice) {
            case 4:
                printf("\nCodigo a remover: ");
                scanf(" %d", &x);
                remove_item(x, products_list);
            break;

            case 3:
                printf("\n\nCodigo a procurar: ");
                scanf(" %d", &x);
                Products *s = malloc(sizeof(Products));
                if(search_list(x, s, products_list)){
                    printf("\nCodigo: %d\nPreco: %.2f\n\n", s->code, s->price);
                }else{
                    printf("Produto nao encontrado\n\n");
                }
                free(s);
                __fpurge(stdin);
                getchar();
            break;

            case 2:
                printf("\nCodigo do produto: ");
                scanf(" %d", &code);
                printf("\nPreco do produto: ");
                scanf(" %f", &price);
                insert_item(code, price, products_list);
            break;

            case 1:
                show_itens(products_list);
                __fpurge(stdin);
                getchar();
            break;

            case 0:
                save_itens(products_list);
                clean_space(products_list);
            break;
        }
    } while (choice);

    free(products_list);
    return 0;
}

