#include <stdlib.h>
#include "header/request.h"

Request* createRequest(Connection* connection, Tipo tipo, char* message) {
    Request* request = (Request*) malloc(sizeof (Request));
    request->connection = connection;
    request->tipo = tipo;
    if (tipo == NONE) {
        strcpy(request->dados, message);
        request->tamanhoTotal = strlen(message);
        request->status = READY;
    } else {
        strcpy(request->url, message);
    }
    request->offset = 0;
    return request;
}

void setStatus(Request* request, Status status) {
    request->status = status;
}

void setTipo(Request* request, Tipo tipo) {
    request->tipo = tipo;
}

void setDados(Request* request, char* dados, int offset) {
    strcpy(request->dados, dados);
    request->offset = offset;
}

void setTamanhoTotal(Request* request, int tamanho) {
    request->tamanhoTotal = tamanho;
}