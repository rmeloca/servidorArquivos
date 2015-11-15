############################# Makefile ##########################
all:
	gcc -c server.c connection.c listDynamic.c requestHandler.c
	gcc -o server server.o connection.o listDynamic.o requestHandler.o -lpthread
	gcc -c client.c connection.c listDynamic.c requestHandler.c
	gcc -o client client.o connection.o listDynamic.o requestHandler.o -lpthread

clean:
	rm -rf *.o
mrproper: clean
	rm -rf main casamento