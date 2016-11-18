/*
    * Lista Dinamicamente Encadeada

    * Arquivo: main_functions.h
    * Descri��o: Biblioteca com as fun��es do programa

    * Codigo por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programa��o II, Rafael Ballotin
    * Engenharia de Computa��o, 2016
*/

typedef struct prods {
    int code;
    float price;
    struct prods *next_position;
} Products;

//Inicia a lista, j� declara a proxima posi��o como NULL
void initialize (Products *products_list) {
    products_list->next_position = NULL;
}

//Verificar se a lista est� vazia ou n�o
int empty_list (Products *products_list) {
    if (products_list->next_position == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//Inserir o item j� no come�o da lista
void insert_item (Products *products_list) {
    Products *new_product = (Products *) malloc(sizeof(Products));

    printf("Codigo do produto: ");
    scanf(" %d", &new_product->code);
    printf("Preco do produto: ");
    scanf(" %f", &new_product->price);

    Products *last_product = products_list->next_position;
    products_list->next_position = new_product;
    new_product->next_position = last_product;
}

void show_itens (Products *products_list) {
    if (empty_list(products_list)) {
        printf("\n\nA lista esta atualmente vazia.\n\n");
        return 0;
    }

    Products *tmp = products_list->next_position;

    while (tmp != NULL) {
        printf("\nCodigo: %d\nPreco: %.2f\n", tmp->code, tmp->price);
        tmp = tmp->next_position;
    }
}

//Liberar o espa�o na memoria
void clean_space (Products *products_list) {
    if (!empty_list(products_list)) { //Se a lista n�o estiver vazia
        Products *next, *current;

        current = products_list->next_position; //Pega a posi��o atual de memoria

        while (current != NULL) { //Enquanto n�o chegar na ultima posi��o
            next = current->next_position;
            free(current);
            current = next;
        }
    }
}

void save_itens (Products *products_list) {
    //FILE *fp = fopen("database.txt", "r+");
    FILE *fp = fopen("products.dat", "r+b");

    if(fp == NULL)
        fp = fopen("products.dat", "w+b");

    Products *tmp = products_list->next_position;

    while (tmp != NULL) {
        //fprintf(fp, "%d %.2f\n", tmp->code, tmp->price);
        fwrite(tmp, sizeof(Products), 1, fp);
        tmp = tmp->next_position;
    }

    fclose(fp);
}

//Na hora de fazer a inser��o do arquivo para o programa, ele vai fazer uma
//adi��o no final da lista, e n�o no inicio
void insert_item_from_stream (Products *products_list, Products *temp) {
    Products *new_product = (Products *) malloc(sizeof(Products));
    new_product->code = temp->code;
    new_product->price = temp->price;
    new_product->next_position = NULL;

    if (empty_list(products_list)) {
        products_list->next_position = new_product;
    } else {
        Products *tmp = products_list->next_position;

        while (tmp->next_position != NULL) {
            tmp = tmp->next_position;
        }

        tmp->next_position = new_product;
    }
}

void load_itens (Products *products_list) {
    int code;
    float price;
    //FILE *fp = fopen("database.txt", "r+");
    FILE *fp = fopen("products.dat", "r+b");
    rewind(fp);

    Products *temp = malloc(sizeof(Products));

    while (fread(temp, sizeof(Products), 1, fp) != NULL) {
        insert_item_from_stream(products_list, temp);
    }

    fclose(fp);
}
