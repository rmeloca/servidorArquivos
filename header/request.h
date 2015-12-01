#pragma once

#include "package.h"
#include "string.h"

/**
 * Define aliases para as tipos construídos
 */
typedef struct connection_t Connection;
typedef struct request Request;
typedef enum status Status;

/**
 * Enum que codifica o estado de cada requisição
 */
enum status {
    READY, SENDING, SENT
};

/**
 * Estrutura responsável por fazer interface entre requestHandler's e worker's.
 * Um pacote oriundo do cliente, recebido pelo tratador de requisições
 * é convertido em requisição e transportado para o buffer de requisições compartilhado entre as threads.
 * Um worker obtém uma requisição e a transforma em um ou muitos pacotes para enviá-lo(s) pela conexão
 */
struct request {
    Connection* connection; //Conexão entre cliente e servidor
    pthread_mutex_t count_mutex;
    pthread_cond_t count_threshold_cv;
    Tipo tipo; //Tipo da requisição solicitada
    char url[MAX_DATA_SIZE]; //caminho absoluto da requisição
    Status status; //Status da requisição
    int maxClientDataSize; //Tamanho máximo que o cliente suporta em cada pacote
};

/**
 * Construtor de requisições. Aloca espaço em memória, popula os dados obrigatórios e os retorna.
 * @param connection Conexão entre os cliente e o servidor.
 * @param tipo Tipo da requisição solicitada. Valor obrigatório.
 * @return Retorna uma requisicao.
 */
Request* createRequest(Connection* connection, Tipo tipo);

/**
 * Altera o status de uma requisição
 * @param request
 * @param status
 */
void setStatus(Request* request, Status status);

/**
 * Altera a url de uma requisição
 * @param request
 * @param url
 */
void setUrl(Request* request, char* url);

/**
 * Altera o valor maxClientDataSize de uma requisição
 * @param request
 * @param maxClientDataSize
 */
void setMaxClientDataSize(Request* request, int maxClientDataSize);