typedef struct inter products;
struct inter {
    int code;
    float price;
    products *next;
};

products * initialyze(products *p1){

    p1 = malloc(sizeof(products));
    p1->code = 0;
    p1->price = 0;
    p1->next = NULL;

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
