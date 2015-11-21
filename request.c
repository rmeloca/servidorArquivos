#include <stdlib.h>
#include "header/request.h"

Request* createRequest(Connection* connection, Tipo tipo) {
    Request* request = (Request*) malloc(sizeof (Request));
    request->connection = connection;
    request->tipo = tipo;
    return request;
}

void setStatus(Request* request, Status status) {
    request->status = status;
}

void setTipo(Request* request, Tipo tipo) {
    request->tipo = tipo;
}

Tipo* getTipo(char* strTipo) {
    Tipo* tipo;
    return tipo;
}