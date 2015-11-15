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
 * calloc(2048, sizeof(char))
 * 
 * ao conectar, exibir ls
 * 
 * shared buffer, chainedList
 * semáforos
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {
    int listenSock;
    char* port;

    if (argc < 2) {
        fprintf(stderr, "uso: %s porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    requestBuffer = createList();
    initializeList(requestBuffer);

    port = argv[1];

    while (1) {
        dispatcher(listenSock, (char*) port);
    }

    close(listenSock);
    return EXIT_SUCCESS;
}

/**
 * Escuta o socket e despacha a conexão para um requestHandler
 * @param listenSock
 * @param port
 */
void dispatcher(int listenSock, char* port) {
    Connection* connection;

    listenSock = CONN_listenTo(port);
    connection = CONN_accept(listenSock);
    if (!connection) {
        fprintf(stderr, "Não foi possível conectar ao cliente remoto na porta %s!\n", port);
        return (EXIT_FAILURE);
    }

    pthread_t* requestHandler;
    requestHandler = malloc(sizeof (pthread_t));
    pthread_create(requestHandler, NULL, createRequestHandler, (void*) connection);
}

int addRequest(Request* request) {
    return addListLast(requestBuffer, request);
}

Request* getRequest() {
    Request* request;
    removeList(requestBuffer, 0, request);
    return request;
}