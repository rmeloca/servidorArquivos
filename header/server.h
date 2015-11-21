#pragma once

#include "listDynamic.h"
#include "requestHandler.h"
#include "worker.h"

/**
 * Estabelece um alias threads da biblioteca pthread.h
 */
typedef pthread_t Thread;

/**
 * Buffer compartilhado entre as threads.
 * Lista encadeada implementada para propósitos gerais
 * Cada posição do buffer consiste em uma requisição do tipo Request
 */
List* requestBuffer;

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
int main(int argc, char** argv);

/**
 * Cria uma abstração para adicionar uma requisição no fim do buffer compartilhado
 * @param request
 * @return 
 */
int addRequest(Request* request);

/**
 * Cria uma abstração para recuperar o primeiro item do buffer
 * @return 
 */
Request* getRequest();

/**
 * Escuta o socket e despacha a conexão para um requestHandler
 * @param listenSock
 * @param port
 */
int dispatcher(int* listenSock, char* port);