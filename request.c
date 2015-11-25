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

void setUrl(Request* request, char* url) {
    strcpy(request->url, url);
}