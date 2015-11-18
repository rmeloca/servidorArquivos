#include <stdlib.h>
#include "header/request.h"

Request* createRequest(Connection* connection, char* message) {
    Request* request = (Request*) malloc(sizeof (Request));
    request->connection = connection;
    strcpy(request->url, message);
    return request;
}