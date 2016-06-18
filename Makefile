.DEFAULT_GOAL := build
.PHONY: build clean

CC=gcc
CFLAGS=-std=c99

risky.o: risky.c risky.h
	$(CC) $(CFLAGS) -c risky.c

risky_boot.o: risky_boot.c
	$(CC) $(CFLAGS) -c risky_boot.c

risky_boot: risky.o risky_boot.o
	$(CC) $(CFLAGS) -g -o risky risky.o risky_boot.o

build: risky_boot

clean:
	rm -f *.o risky
