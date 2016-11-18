/*
    * Lista Dinamicamente Encadeada

    * Arquivo: main_functions.h
    * Descrição: Biblioteca com as funções do programa

    * Codigo por:

    * Adolpho F. Z. Piazza
    * Matheus Nava
    * Rafael F. Filho

    * Algoritmos e Programação II, Rafael Ballotin
    * Engenharia de Computação, 2016
*/

typedef struct prods {
    int code;
    float price;
    struct prods *next_position;
} Products;

//Inicia a lista, já declara a proxima posição como NULL
void initialize (Products *products_list) {
    products_list->next_position = NULL;
}

//Verificar se a lista está vazia ou não
int empty_list (Products *products_list) {
    if (products_list->next_position == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int check_list (int code, Products *products_list) {
    if (!empty_list(products_list)) {
        while (products_list->next_position != NULL) {
            if (code == products_list->code) {
                return 1;
            }
            products_list = products_list->next_position;
        }
    }
    return 0;
}

//Inserir o item já no começo da lista
void insert_item (Products *products_list) {
    Products *new_product = (Products *) malloc(sizeof(Products));

    printf("Codigo do produto: ");
    scanf(" %d", &new_product->code);
    printf("Preco do produto: ");
    scanf(" %f", &new_product->price);

    if (check_list(new_product->code, products_list)) {
        Products *last_product = products_list->next_position;
        products_list->next_position = new_product;
        new_product->next_position = last_product;
    } else {
        printf("Codigo ja existente\n");
    }
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

//Liberar o espaço na memoria
void clean_space (Products *products_list) {
    if (!empty_list(products_list)) { //Se a lista não estiver vazia
        Products *next, *current;

        current = products_list->next_position; //Pega a posição atual de memoria

        while (current != NULL) { //Enquanto não chegar na ultima posição
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

//Na hora de fazer a inserção do arquivo para o programa, ele vai fazer uma
//adição no final da lista, e não no inicio
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
    //FILE *fp = fopen("database.txt", "r+");
    FILE *fp = fopen("products.dat", "r+b");
    rewind(fp);

    Products *temp = malloc(sizeof(Products));

    while (fread(temp, sizeof(Products), 1, fp) != NULL) {
        insert_item_from_stream(products_list, temp);
    }

    fclose(fp);
}

Products * search_list (int search_code, Products *products_list) {
    Products *s = products_list;
    while (s != NULL && s->code != search_code) {
        s = s->next_position;
    }
    return s;
}

void remove_item (int x, Products *products_list) {
    Products *rafael, *ballotin;
    rafael = products_list;
    ballotin = products_list->next_position;
    while (ballotin != NULL && ballotin->code != x) {
          rafael = ballotin;
          ballotin = ballotin->next_position;
    }
    if (ballotin != NULL) {
          rafael->next_position = ballotin->next_position;
          free(ballotin);
    }
}
