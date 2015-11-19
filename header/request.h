#pragma once

#include "string.h"

typedef struct request Request;
typedef struct connection_t Connection;
typedef enum tipo Tipo;
typedef enum status Status;

#define MAX_URL_SIZE 2048
#define MAX_DATA_SIZE 2048

enum tipo {
    LS, WGET, NONE
};

enum status {
    READY, SENDING, SENT
};

struct request {
    Connection* connection;
    char url[MAX_URL_SIZE];
    Tipo tipo;
    Status status;
    char dados[MAX_DATA_SIZE];
    int offset;
//    int tamanho;//embutido em strlen(dados)?
    int tamanhoTotal;
};

Request* createRequest(Connection* connection, Tipo tipo, char* message);
void setStatus(Request* request, Status status);
void setDados(Request* request, char* dados, int offset);
void setTamanhoTotal(Request* request, int tamanho);