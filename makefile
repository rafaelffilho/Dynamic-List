all : menu.c list.h main.c
	gcc -o test main.c menu.c -lncurses -lmenu -Wall
