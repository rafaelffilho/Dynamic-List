#include "prod.h"

struct Product{int code;float price;} * initialize_list(struct Product *p1, FILE **fp, int *size){

    *fp = fopen("products.dat", "r+b");

    if(*fp == NULL)
        *fp = fopen("products.dat", "w+b");

    int tam = 0;
    int i;

    p1 = malloc(sizeof(Product));

    while(fread(&p1[0], sizeof(Product), 1, *fp) != NULL){
        tam++;
    }

    if(tam > 1){
        rewind(*fp);

        p1 = malloc((tam) * sizeof(*p1));

        for (int i = 0; i < tam; i++){
            fread(&p1[i], sizeof(Product), 1, *fp);
        }
    }

    rewind(*fp);

    *size = tam;

    return  p1;
}

struct Product * add_product(struct Product *p1, int *size, int code, int price){

    int i;

    for (i = 0; i < *size; i++) {
        if (p1[i].code == code) {
            fputs("\nAlready have a product with this code.\nPress enter to go to menu", stderr);
            getchar();
            getchar();
            return p1;
        }
    }

    Product *newP = realloc(p1, (*size+1) * sizeof(Product));
    p1 = newP;

    for (i = *size; i > 0; i--) {
        p1[i].code = p1[i-1].code;
        p1[i].price = p1[i-1].price;
    }

    p1[0].code = code;
    p1[0].price = price;

    *size = *size + 1;

    return p1;
}

struct Product * del_product(struct Product *p1, int *size, int code){

    int i;
    int q;

    for (i = 0; i < *size; i++) {
        if (p1[i].code == code) {
            for (q = i; q < *size; q++) {
                p1[q].code = p1[q+1].code;
                p1[q].price = p1[q+1].price;
            }
            i = *size;
            *size = *size - 1;
        }
    }

    Product *newP = realloc(p1, (*size) * sizeof(Product));
    p1 = newP;

    return p1;
}
