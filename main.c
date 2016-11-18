/*
    * Lista Dinamicamente Encadeada

    * Arquivo: main.c
    * Descri��o: Estrutura principal do programa

    * Codigo por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programa��o II, Rafael Ballotin
    * Engenharia de Computa��o, 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main () {

    Products *products_list = (Products *) malloc(sizeof(Products));
    initialize(products_list);
    load_itens(products_list);

    int control = 1, choice;

    do {
        printf("2 - Adicionar produto\n1 - Listar items\n0 - Sair\n-> ");
        scanf(" %d", &choice);

        switch (choice) {
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
