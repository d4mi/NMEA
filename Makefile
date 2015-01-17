CC=gcc
CFLAGS=-std=c89 -pedantic -I.

gps: GpsParser.c main.c
	$(CC) GpsParser.c main.c -o gps $(CFLAGS)