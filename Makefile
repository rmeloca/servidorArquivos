CC=gcc
LDFLAGS=-lpthread
CFLAGS=-O0 -ggdb

all: 
	$(CC) -c connection.c $(CFLAGS)
	$(CC) -o client client.c connection.o $(LDFLAGS)
	$(CC) -o server server.c connection.o $(LDFLAGS)
