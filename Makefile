############################# Makefile ##########################
all:
	gcc -c server.c connection.c listDynamic.c requestHandler.c request.c package.c worker.c -Wall -ggdb
	gcc -o server server.o connection.o listDynamic.o requestHandler.o request.o package.o worker.o -lpthread -ggdb
	gcc -c client.c connection.c package.c -Wall -ggdb
	gcc -o client client.o connection.o package.o -lpthread -ggdb

clean:
	rm -rf *.o
mrproper: clean
	rm -rf client server
