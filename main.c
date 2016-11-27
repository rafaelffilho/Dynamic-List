/*
    * Lista Dinamicamente Encadeada

    * Arquivo: main.c
    * Descrição: Estrutura principal do programa

    * Código por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programação II, Rafael Ballotin
    * Engenharia de Computação, 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "struct.h"

int main () {

    Products *products_list = (Products *) malloc(sizeof(Products));
    initialize(products_list);
    load_itens(products_list);

    while (main_menu(products_list) != NULL);

    save_itens(products_list);
    clean_space(products_list);

    free(products_list);
    return 0;
}
