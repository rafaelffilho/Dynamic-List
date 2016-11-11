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

struct Product * add_product(struct Product *products, int *size, int code, int price){

    int i;

    Product *newP = realloc(products, (*size+1) * sizeof(Product));
    products = newP;

    for (i = *size; i > 0; i--) {
        products[i].code = products[i-1].code;
        products[i].price = products[i-1].price;
    }

    products[0].code = code;
    products[0].price = price;

    *size = *size + 1;

    return products;
}
