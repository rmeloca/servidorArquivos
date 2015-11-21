############################# Makefile ##########################
all:
	gcc -c server.c connection.c listDynamic.c requestHandler.c request.c package.c -Wall
	gcc -o server server.o connection.o listDynamic.o requestHandler.o request.o package.o -lpthread
	gcc -c client.c connection.c package.c -Wall
	gcc -o client client.o connection.o package.o -lpthread

clean:
	rm -rf *.o
mrproper: clean
	rm -rf client server
