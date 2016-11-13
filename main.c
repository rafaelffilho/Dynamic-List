#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[]) {

    FILE *fp;
    products *p1;

    int code;
    int choice = 1;
    float price;

    p1 = initialyze(p1, &fp);

    do {

        printf("Type the code: ");
        scanf(" %d", &code);
        printf("Type the price: ");
        scanf(" %f", &price);

        insert(code, price, p1);

        printf("\n0 - exit ");
        scanf(" %d", &choice);

    } while(choice);

    print_list(p1);

    save_to_file(p1, &fp);

    free(p1);

    fclose(fp);

    return 0;
}
