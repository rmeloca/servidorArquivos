#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "header/server.h"

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
    sem_init(&mutexVouMexerNaLista, 0, 1);//Lista disponível para adições
    sem_init(&mutexPossoConsumir, 0, 0);//Lista Vazia Mutex Ocupado

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
    sem_destroy(&mutexVouMexerNaLista);
    sem_destroy(&mutexPossoConsumir);
    return EXIT_SUCCESS;
}

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
    sem_wait(&mutexVouMexerNaLista);
    return addListLast(requestBuffer, request);
    sem_post(&mutexVouMexerNaLista);
    sem_post(&mutexPossoConsumir);
}

Request* getRequest() {
    Request* request = NULL;
    sem_wait(&mutexPossoConsumir); //Se interromper aqui?
    sem_wait(&mutexVouMexerNaLista);
    removeList(requestBuffer, 0, request);
    if (isEmptyList(requestBuffer)) {
        sem_post(&mutexPossoConsumir);
    }
    sem_post(&mutexVouMexerNaLista);
    return request;
}