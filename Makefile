CC = gcc
CFLAGS = -Wall -ggdb -lm

DOP: main.c matrix_tools.c
	$(CC) $(CFLAGS) -o a.out -std="c99" main.c matrix_tools.c
