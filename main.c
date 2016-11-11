#include <stdio.h>
#include "list.h"
#include "prod.h"

int main(int argc, char const *argv[]) {

    Product *products;
    Product *searchp;
    FILE *fp;

    int i;
    int control=1;
    int tam;
    int choice;
    int code;
    float price;

    products = initialize_list(products, &fp, &tam);

    searchp = malloc(sizeof(Product));

    do {

        system("clear");
        printf("1  - Add product\n2  - Delete a product\n3  - Show all products\n4  - Search product\n99 - Exit\n-> ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:

                system("clear");

                printf("\nDigit the product code: ");
                scanf(" %d", &code);
                printf("Digit the product price: ");
                scanf(" %f", &price);

                products = add_product(products, &tam, code, price);

            break;
            case 2:

                system("clear");

                printf("\nDigit the code of product to delete: ");
                scanf(" %d", &code);

                del_product(products, &tam, code);

                break;
            case 3:

                system("clear");

                if (tam == 0) {
                    printf("The list is empty.\n");
                } else {
                    for (i = 0; i < tam; i++) {
                        printf("\nProduct code: %d\nProduct price: %.2f\n", products[i].code, products[i].price);
                    }
                }

                printf("\n\nPress ENTER to go to menu...\n");
                __fpurge(stdin);
                getchar();

                break;
            case 4:

                system("clear");

                printf("\nDigit the code for search: ");
                scanf(" %d", &code);

                searchp = search_product(products, &tam, code);

                if (searchp == NULL) {

                    printf("\n0 - Product not found.\n");
                    printf("\nPress ENTER to go to menu...\n");

                    __fpurge(stdin);
                    getchar();

                    break;
                }

                printf("\nProduct code: %d\nProduct price: %.2f\n", searchp[0].code, searchp[0].price);
                printf("\n\nPress ENTER to go to menu...\n");

                __fpurge(stdin);
                getchar();

                break;
            case 99:
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
