#ifndef THISLIB
#define  THISLIB

typedef struct prods {
    int code;
    float price;
    struct prods *next_position;
} Products;

#endif
