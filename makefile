all : menu.c list.h main.c
	gcc -o list main.c menu.c -lncurses -lmenu -Wall
