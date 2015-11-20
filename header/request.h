#pragma once

#include "string.h"

typedef struct request Request;
typedef struct connection_t Connection;
typedef enum tipo Tipo;
typedef enum status Status;

#define MAX_URL_SIZE 2048
//max data size 2048 - 4 - 4
#define MAX_DATA_SIZE 2048

enum tipo {
    LS, WGET, NONE
};

enum status {
    READY, SENDING, SENT
};

struct request {
    Connection* connection;
    Tipo tipo;
    char url[MAX_URL_SIZE];
    Status status;
    //adicionar uma referência para uma lista de pacotes
    //lista dinâmica ou vetor?
    //agrupar em uma estrutura Package
    int tamanhoTotal;
    int offset;
    char dados[MAX_DATA_SIZE];
};

Request* createRequest(Connection* connection, Tipo tipo, char* message);
void setStatus(Request* request, Status status);
void setTipo(Request* request, Tipo tipo);
void setDados(Request* request, char* dados, int offset);
void setTamanhoTotal(Request* request, int tamanho);