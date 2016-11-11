#include <stdio.h>
#include "list.h"
#include "prod.h"

int main(int argc, char const *argv[]) {

    Product *products;
    FILE *fp;

    int i;
    int control=1;
    int tam;
    int choice;
    int code;
    float price;

    products = initialize_list(products, &fp, &tam);


    do {
      system("clear");
        printf("1 - Add product\n2 - Show all products\n3 - Exit\n-> ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:

            printf("Digit the product code: ");
            scanf(" %d", &code);
            printf("Digit the product price: ");
            scanf(" %f", &price);

            products = add_product(products, &tam, code, price);

            break;
            case 2:
            system("clear");
            if (tam == 0) {
                printf("The list is empty.\n");
            } else {
                for (i = 0; i < tam; i++) {
                    printf("\nProduct code: %d\nProduct price: %f\n", products[i].code, products[i].price);
                }
            }
            printf("\n\nPress ENTER to go to menu...\n");
            getchar();
            getchar();
            break;
            case 3:
                control = 0;
            break;
        }

    } while (control);

    for (int i = 0; i < tam; i++){
        fwrite(&products[i], sizeof(Product), 1, fp);
    }

    fclose(fp);

    free(products);

    return 0;
}
