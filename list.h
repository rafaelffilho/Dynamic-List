typedef struct inter products;
struct inter {
    int code;
    float price;
    products *next;
};

products * initialyze(products *p1, FILE **fp){

    *fp = fopen("products.dat", "r+b");

    if(*fp == NULL)
        *fp = fopen("products.dat", "w+b");

    p1 = malloc(sizeof(products));

    //if((fread(p1, sizeof(products), 1, *fp)) == NULL){
        p1->code = 0;
        p1->price = 0;
        p1->next = NULL;
    //}

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
    fwrite(p1, sizeof(products), 1, *fp);
}
