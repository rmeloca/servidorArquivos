#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "header/server.h"

/**
 * Inicializa o servidor e o prepara para receber várias conexões
 * 
 * ls /
 * ls
 * ls /fotos
 * wget /foto.png
 * wget /dados/arquivo.csv
 * 
 * semáforos
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    int* listenSock;
    char* port;
    int numeroWorkers;

    if (argc < 2) {
        fprintf(stderr, "uso: %s porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    port = argv[1];
    listenSock = malloc(sizeof (int));
    *listenSock = 0;
    numeroWorkers = 1;

    requestBuffer = createList();
    initializeList(requestBuffer);

    //Cria worker threads
    Thread* worker;
    int i;
    for (i = 0; i < numeroWorkers; i++) {
        worker = malloc(sizeof (Thread));
        pthread_create(worker, NULL, listenBuffer, NULL);
    }

    //escuta o socket
    while (!dispatcher(listenSock, port));

    close(*listenSock);
    return EXIT_SUCCESS;
}

/**
 * Escuta o socket e despacha a conexão para um requestHandler
 * @param listenSock
 * @param port
 */
int dispatcher(int* listenSock, char* port) {
    Connection* connection;

    *listenSock = CONN_listenTo(port);
    connection = CONN_accept(*listenSock);
    if (!connection) {
        fprintf(stderr, "Não foi possível conectar ao cliente remoto na porta %s!\n", port);
        return EXIT_FAILURE;
    }

    Thread* requestHandler;
    requestHandler = malloc(sizeof (Thread));
    pthread_create(requestHandler, NULL, createRequestHandler, (void*) connection);
    return EXIT_SUCCESS;
}

int addRequest(Request* request) {
    return addListLast(requestBuffer, request);
}

Request* getRequest() {
    Request* request = NULL;
    removeList(requestBuffer, 0, request);
    return request;
}