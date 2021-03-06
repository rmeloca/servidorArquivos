#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include "header/server.h"

List* requestBuffer;
Mutex vouMexerNaLista;
Semaphore possoConsumir;

int main(int argc, char** argv) {
    int* listenSock;
    char* port;
    int numeroWorkers;

    if (argc < 3) {
        fprintf(stderr, "uso: %s porta workers\n", argv[0]);
        return EXIT_FAILURE;
    }

    port = argv[1];
    listenSock = malloc(sizeof (int));
    *listenSock = 0;
    
    numeroWorkers = atoi(argv[2]);

    requestBuffer = createList();
    initializeList(requestBuffer);

    sem_init(&possoConsumir, 0, 0); //Lista disponível para adições
    pthread_mutex_init(&vouMexerNaLista, NULL);

    //Cria worker threads
    Thread* worker;
    int i;
    for (i = 0; i < numeroWorkers; i++) {
        worker = malloc(sizeof (Thread));
        pthread_create(worker, NULL, listenBuffer, NULL);
    }

    *listenSock = CONN_listenTo(port);
    //escuta o socket
    while (!dispatcher(listenSock, port));

    close(*listenSock);
    sem_destroy(&possoConsumir);
    pthread_mutex_destroy(&vouMexerNaLista);
    return EXIT_SUCCESS;
}

int dispatcher(int* listenSock, char* port) {
    Connection* connection;
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
    pthread_mutex_lock(&vouMexerNaLista);
    addListLast(requestBuffer, request);
    pthread_mutex_unlock(&vouMexerNaLista);
    sem_post(&possoConsumir);
    return 1;
}

Request* getRequest() {
    Request* request = NULL;
    sem_wait(&possoConsumir);
    pthread_mutex_lock(&vouMexerNaLista);

    Node* removed;
    removed = requestBuffer->first;
    requestBuffer->first = removed->next;
    requestBuffer->size--;
    request = removed->data;
    free(removed);
    
    pthread_mutex_unlock(&vouMexerNaLista);
    return request;
}