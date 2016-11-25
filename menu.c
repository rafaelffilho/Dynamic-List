#ifdef _WIN32

#include <windows.h>
#include "struct.h"


void gotoxy(int x, int y){

  COORD coord={0,0};

  coord.X=x;

  coord.Y=y;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}



void menu(Products *products_list){      // subrotina para printar as bordas do menu



  gotoxy(32, 3);puts("ADD PRODUCT");

  gotoxy(32, 4);puts("SEARCH PRODUCT");

  gotoxy(32, 5);puts("REMOVE PRODUCT");

  gotoxy(32, 6);puts("SHOW LIST");

  gotoxy(32, 7);puts("EXIT");

  gotoxy(4, 9);puts("List:");



  int cont;



  gotoxy(2, 1); printf("%c", 201);

  gotoxy(77,1); printf("%c", 187);    //printar as quinas



  for(cont=3; cont<77; cont++){

    gotoxy(cont, 1); printf("%c", 205);

    gotoxy(cont, 9); printf("%c", 205);   //printar as colunas horizontais

  }



  for(cont=2; cont<9; cont++){

      gotoxy(77, cont); printf("%c", 186);   // printar as linhas verticais

      gotoxy(2, cont); printf("%c", 186);

  }

}



int cursor(int cy, int ys, int yi, int wv){ // a função recebe valores fornecidos pelo programador

  while(1){

    if(kbhit()){

      switch(getch()){

        case 72:

          cy-=wv;

          if(cy <= ys)

            cy=ys;

          break;



        case 80:

          cy+=wv;

          if(cy >= yi)

            cy=yi;

          break;



        case 13:

          return cy;

      }

    }

    Sleep(20);

    gotoxy (29, cy);puts(">>");



    Sleep(10);

    gotoxy (29, cy);printf(" ");

    gotoxy (30, cy);printf(" ");

  }

}



void show_itens (Products *products_list, int *i) {

  if (empty_list(products_list)) {

    gotoxy(2, 9); printf("%c", 200);

    gotoxy(77, 9); printf("%c", 188);

    gotoxy(32, 11);printf("List is empty.");

    return 0;

  }



  Products *tmp = products_list->next_position;

  int j=11;



  while (tmp != NULL){

    gotoxy(77, j-1);printf("%c", 186);

    gotoxy(2, j-1);printf("%c", 186);

    gotoxy(77, j+1);printf("%c", 186);

    gotoxy(2, j+1);printf("%c", 186);

    gotoxy(77, j+2);printf("%c", 186);

    gotoxy(2, j+2);printf("%c", 186);

    gotoxy(77, j);printf("%c", 186);

    gotoxy(2, j);printf("%c", 186);

    gotoxy(32, j);printf("Code: %d", tmp->code);

    gotoxy(32, j+1);printf("Price: %.2f", tmp->price);

    tmp = tmp->next_position;

    j+=3;

  }

  for(int cont=3; cont<77; cont++){

    gotoxy(cont, j); printf("%c", 205);

  }

  gotoxy(2, 9);printf("%c", 204);

  gotoxy(77, 9);printf("%c", 185);

  gotoxy(2, j); printf("%c", 200);

  gotoxy(77, j); printf("%c", 188);



  *i=j;

}



int main_menu(Products *products_list){


    int code;
    float price;
    int x;
    int i=11;

    system("cls");

    show_itens(products_list, &i);

    menu(products_list);



    switch (cursor(3, 3, 7, 1)) {

      case 5:

        gotoxy(55, 3);printf("Remove code: ");

        scanf(" %d", &x);

        if (check_list(x, products_list)){

          gotoxy(55, 5);printf("Product not found");

          gotoxy(48, 8);puts("Press any key to continue...");

          getch();

        }else{

          remove_item(x, products_list);

          i-=3;

        }

      break;



      case 4:

        gotoxy(55, 3);printf("Seek code: ");

        scanf(" %d", &x);

        Products *s = malloc(sizeof(Products));

        if(search_list(x, s, products_list)){

          gotoxy(55, 5);printf("Code: %d", s->code);

          gotoxy(55, 6);printf("Price: %.2f", s->price);

        }else{

          gotoxy(55, 5);printf("Product not found");

        }

        gotoxy(48, 8);puts("Press any key to continue...");

        getch();

      break;



      case 3:

        gotoxy(55, 2);printf("Product code: ");

        scanf(" %d", &code);

        gotoxy(55, 3);printf("Product price: ");

        scanf(" %f", &price);

        if (check_list(code, products_list)){

          insert_item(&code, &price, products_list);

          i+=3;

        }else{

          gotoxy(50, 5);printf("The product already exist");

          gotoxy(48, 8);puts("Press any key to continue...");

          getch();

        }

      break;



      case 6:

        if(empty_list(products_list)){

          gotoxy(55, 11);

          cursor(11, 11, i, 3);

        }else{

          gotoxy(55, i-2);

          cursor(11, 11, i-3, 3);

        }

      break;



      case 7:
        return NULL;

      //break;

    }

}

#else

#include <ncurses.h>
#include <menu.h>
//#include "list.h"
#include "struct.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void draw_list(Products *products_list) {

    if (empty_list(products_list)) {
        printf("\n\nEmpty list.\n\n");
        return ;
    }

    Products * temp = products_list->next_position;

    for (int i = 0; i < LINES - 2; i += 3) {
        mvprintw(i, COLS - 46, "Product code: %d", temp->code);
        mvprintw(i + 1, COLS - 46, "Product price: %.2f", temp->price);
        temp = temp->next_position;
        if (temp == NULL)
            break;
    }
    if (temp != NULL) {
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

    mvprintw(1, 1, "Code: ");
    __fpurge(stdin);
    scanw(" %d", &code);
    mvprintw(3, 1, "Price: ");
    __fpurge(stdin);
    scanw(" %f", &price);

    if(insert_item (&code, &price, products_list) == NULL){
        mvprintw(5, 1, "*Code already in use*");
        __fpurge(stdin);
        getch();
        return;
    }

    mvprintw(5, 1, "*Added product*");

    __fpurge(stdin);
    getch();
}

void remove_menu(Products *products_list){

    int code;

    draw_list(products_list);

    Products *temp;

    mvprintw(1, 1, "Code: ");
    scanw(" %d", &code);

    if (search_list(code, temp, products_list)) {

        remove_item(code, products_list);
        mvprintw(5, 1, "*Removed product*");
    } else {
        mvprintw(5, 1, "*Code not found*");
    }

    __fpurge(stdin);
    getch();
}

void search_menu(Products *products_list){

    int code;

    draw_list(products_list);

    mvprintw(1, 1, "Code: ");
    __fpurge(stdin);
    //move(row,col);
    scanw(" %d", &code);
    //getstr(str);
    //x = atoi(str);
    Products *s = malloc(sizeof(Products));
    //refresh();
    if(search_list(code, s, products_list)){
        //printf("\nCódigo: %d\nPreço: %.2f\n\n", s->code, s->price);
        mvprintw(4, 1, "Code: %d", s->code);
        mvprintw(5, 1, "Price: %.2f", s->price);
    }else{
        mvprintw(4, 1, "*Code not found*");
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
        "Add product",
        "Remove product",
        "Search product",
        "Exit",
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

#endif
