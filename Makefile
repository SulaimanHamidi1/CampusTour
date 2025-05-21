CC = gcc
CFLAGS = -g -O0 -Wall -std=c99 -pedantic-errors -D_GNU_SOURCE
LIBS = -lm

all:
	$(CC) $(CFLAGS) OnlineCampusTour.c -o OnlineCampusTour $(LIBS)

clean:
	rm -f OnlineCampusTour

