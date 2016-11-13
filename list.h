typedef struct inter products;
struct inter {
    int code;
    float price;
    products *next;
};

int tam;

void read_file(products *p1, FILE **fp){

    products *temp;
    temp = malloc(sizeof(products));

    tam = 0;

    while (fread(temp, sizeof(products), 1, *fp) != NULL) {
        tam++;
    }

    rewind(*fp);

    for (int i = 0; i < tam; p1 = p1->next) {
        fread(temp,sizeof(products), 1, *fp);
        temp->next = p1->next;
        p1->next = temp;
        i++;
    }
    p1->next = NULL;
}

products * initialyze(products *p1, FILE **fp){

    int tam = 0;

    *fp = fopen("products.dat", "r+b");

    if(*fp == NULL)
        *fp = fopen("products.dat", "w+b");

    p1 = malloc(sizeof(products));

    p1->code = 0;
    p1->price = 0;
    p1->next = NULL;

    read_file(p1, fp);

    return p1;
}

void insert (int code, float price, products *p1){
   products *temp;
   temp = malloc(sizeof(products));
   temp->code = code;
   temp->price = price;
   temp->next = p1->next;
   p1->next = temp;
}

void print_list (products *p1) {
   if (p1 != NULL && p1->code != 0 && p1->price != 0){
        printf ("\nCode: %d\nPrice: %.2f\n", p1->code, p1->price);
        if (p1->next == NULL)
            return;
        print_list (p1->next);
    } else if (p1->code == 0 && p1->price == 0){
        print_list(p1->next);
    }
}

void save_to_file(products *p1, FILE **fp){

    for(int i = 0; i < tam-1; i++){
        fwrite(p1, sizeof(products), 1, *fp);
        p1 = p1->next;
    }
}
