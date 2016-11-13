typedef struct inter products;
struct inter {
    int code;
    float price;
    products *next;
};

void insert (int code, float price, products *p1){
   products *temp;
   temp = malloc(sizeof (products));
   temp->code = code;
   temp->price = price;
   temp->next = p1->next;
   p1->next = temp;
}

void print_list (products *p1) {
   if (p1 != NULL) {
      printf ("\nCode: %d\nPrice: %.2f\n", p1->code, p1->price);
      print_list (p1->next);
   }
}
