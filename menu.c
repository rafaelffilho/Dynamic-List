#include <ncurses.h>
#include <menu.h>
//#include "list.h"
#include "struct.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void draw_list(Products *products_list) {

    if (empty_list(products_list)) {
        printf("\n\nA lista esta atualmente vazia.\n\n");
        return ;
    }

    Products * temp = products_list->next_position;

    for (int i = 0; i < LINES - 2; i += 3) {
        mvprintw(i, COLS - 46, "Product code: %d", temp->code);
        mvprintw(i + 1, COLS - 46, "Product price: %.2f", temp->price);
        if (temp->next_position == NULL)
            break;
        temp = temp->next_position;
    }
    if (temp->next_position != NULL) {
        for (int i = 0; i < LINES - 2; i += 3) {
            mvprintw(i, COLS - 22, "Product code: %d", temp->code);
            mvprintw(i + 1, COLS - 22, "Product price: %.2f", temp->price);
            if (temp->next_position == NULL)
                break;
            temp = temp->next_position;
        }
    }
}

void draw_main_menu(MENU *menu, Products *products_list, int *curr){
    clear();
    post_menu(menu);
    draw_list(products_list);
    refresh();
    menu_driver(menu, REQ_FIRST_ITEM);
    *curr = 0;
}

void add_menu(Products *products_list){

    int code;
    float price;

    draw_list(products_list);

    mvprintw(1, 1, "Codigo a adicionar: ");
    __fpurge(stdin);
    scanw(" %d", &code);
    mvprintw(3, 1, "Preco do produto: ");
    __fpurge(stdin);
    scanw(" %f", &price);

    if(insert_item (&code, &price, products_list) == NULL){
        mvprintw(5, 1, "*Codigo ja existente*");
        __fpurge(stdin);
        getch();
        return;
    }

    mvprintw(5, 1, "*Produto adicionado*");

    __fpurge(stdin);
    getch();
}

void remove_menu(Products *products_list){

    int code;

    draw_list(products_list);

    mvprintw(1, 1, "Codigo a remover: ");
    scanw(" %d", &code);
    remove_item(code, products_list);

    mvprintw(5, 1, "*Produto removido*");

    __fpurge(stdin);
    getch();
}

void search_menu(Products *products_list){

    int code;

    draw_list(products_list);

    mvprintw(1, 1, "Codigo a procurar: ");
    __fpurge(stdin);
    //move(row,col);
    scanw(" %d", &code);
    //getstr(str);
    //x = atoi(str);
    Products *s = malloc(sizeof(Products));
    //refresh();
    if(search_list(code, s, products_list)){
        //printf("\nCódigo: %d\nPreço: %.2f\n\n", s->code, s->price);
        mvprintw(4, 1, "Codigo: %d", s->code);
        mvprintw(5, 1, "Preco: %.2f", s->price);
    }else{
        mvprintw(4, 1, "*Codigo nao encontrado*");
    }
    free(s);
    __fpurge(stdin);
    getch();
}

int main_menu(Products *products_list){

    ITEM **items;
    int c;
    MENU *menu;
    int n_options;
    int i;
    int curr = 0;

    char *options[] = {
        "Adicionar produto",
        "Remover produto",
        "Procurar produto",
        "Sair",
    };

    initscr();
    cbreak();
    //noecho();
    keypad(stdscr, TRUE);

    n_options = ARRAY_SIZE(options);
    items = calloc(n_options + 1, sizeof(ITEM *));

    for(i = 0; i < n_options; ++i)
        items[i] = new_item(options[i], "");

    items[n_options] = NULL;

    menu = new_menu(items);
    clear();
    post_menu(menu);
    draw_list(products_list);
    refresh();

    while((c = getch()) != KEY_F(2)){
        switch(c){
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                if (curr < 3)
                    curr++;
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                if (curr > 0)
                    curr--;
                break;
            default:
                switch (curr) {
                    case 0:
                        clear();
                        add_menu(products_list);
                        menu_driver(menu, REQ_LAST_ITEM);
                        draw_main_menu(menu, products_list, &curr);
                        break;
                    case 1:
                        clear();
                        remove_menu(products_list);
                        draw_main_menu(menu, products_list, &curr);
                        break;
                    case 2:
                        clear();
                        search_menu(products_list);
                        draw_main_menu(menu, products_list, &curr);
                        break;
                    case 3:
                        free_item(items[0]);
                        free_item(items[1]);
                        free_menu(menu);
                        endwin();
                        return NULL;
                        break;
                }
        }
    }

    free_item(items[0]);
    free_item(items[1]);
    free_menu(menu);
    endwin();
}
