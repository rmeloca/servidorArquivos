#include "header/request.h"

Request* createRequest(Connection* connection, char* message) {
    Request* request = (Request*) malloc(sizeof (Request));
    request->connection = connection;
    request->url = (char*) calloc(strlen(message), sizeof (char));
    strcpy(request->url, message);
    return request;
}