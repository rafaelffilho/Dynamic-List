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
#include "main_functions.h"

int main () {

    Products *products_list = (Products *) malloc(sizeof(Products));
    initialize(products_list);
    load_itens(products_list);

    int control = 1, choice, x;

    do {
        printf("4 - Remover um item\n3 - Procurar produto\n2 - Adicionar produto\n1 - Listar items\n0 - Sair\n-> ");
        scanf(" %d", &choice);

        switch (choice) {
            case 4:
                printf("Codigo a remover: ");
                scanf(" %d", &x);
                //Products *r = search_list(x, products_list);
                remove_item(x, products_list);
            break;

            case 3:
                printf("Codigo a procurar: ");
                scanf(" %d", &x);
                Products *s = search_list(x, products_list);
                printf("\nCodigo: %d\nPreco: %.2f\n", s->code, s->price);
            break;

            case 2:
                insert_item(products_list);
            break;

            case 1:
                show_itens(products_list);
            break;

            case 0:
                save_itens(products_list);
                clean_space(products_list);
                control = 0;
            break;
        }
    } while (control);
}
