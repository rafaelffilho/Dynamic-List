#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[]) {

    products *p1;

    int code;
    float price;

    p1 = malloc(sizeof(products));
    p1->next = NULL;

    printf("Type the code: ");
    scanf(" %d", &code);
    printf("Type the price: ");
    scanf(" %f", &price);

    insert(code, price, p1);


    printf("Type the code: ");
    scanf(" %d", &code);
    printf("Type the price: ");
    scanf(" %f", &price);

    insert(code, price, p1);

    print_list(p1);

    return 0;
}
