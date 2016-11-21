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

//função recursiva para verificar se o código ja existe
int check_list (int code, Products *products_list) {
    if(code == products_list->code){
        return 0;
    }else if(products_list->next_position == NULL){
        return 1;
    }else{
        check_list(code, products_list->next_position);
    }
}

//Inserir o item já no começo da lista
void insert_item (int code, float price, Products *products_list) {
    Products *new_product = (Products *) malloc(sizeof(Products));

    new_product->code = code;
    new_product->price = price;

    if (check_list(new_product->code, products_list)) {
        Products *last_product = products_list->next_position;
        products_list->next_position = new_product;
        new_product->next_position = last_product;
    } else {
        printf("Codigo ja existente\n");
        //system("\npause");
		__fpurge(stdin);
		getchar();
    }
}

void show_itens (Products *products_list) {
    if (empty_list(products_list)) {
        printf("\n\nA lista esta atualmente vazia.\n\n");
        return ;
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
    FILE *fp = fopen("products.dat", "w+b");

    //if(fp == NULL)
      //  fp = fopen("products.dat", "w+b");

    //rewind(fp);

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
    FILE *fp = fopen("products.dat", "r+b");

    rewind(fp);

    Products *temp = malloc(sizeof(Products));

    while (fread(temp, sizeof(Products), 1, fp) != NULL) {
        insert_item_from_stream(products_list, temp);
    }

    free(temp);
    fclose(fp);
}

//função recursiva para procurar o produto (não da erro quando não acha) ps: chupa adolpho
int search_list (int search_code, Products *s, Products *products_list) {
    if(search_code == products_list->code){
        s->code = products_list->code;
        s->price = products_list->price;
        return 1;
    }else if(products_list->next_position == NULL){
        return 0;
    }else{
        search_list(search_code, s, products_list->next_position);
    }
}

void remove_item (int x, Products *products_list) {
    Products *trash, *trashProx;
    trash = products_list;
    trashProx = products_list->next_position;
    while (trashProx != NULL && trashProx->code != x) {
          trash = trashProx;
          trashProx = trashProx->next_position;
    }
    if (trashProx != NULL) {
          trash->next_position = trashProx->next_position;
          free(trashProx);
    }
}
