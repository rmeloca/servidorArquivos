#pragma once

#include "string.h"

typedef struct request Request;
typedef struct connection_t Connection;
typedef enum tipo Tipo;
typedef enum status Status;

#define MAX_DATA_SIZE 2048

enum tipo {
    LS, WGET, WELCOME, MAXPACKAGESIZE, FILENOTEXIST, CLOSECONNECTION, OTHER
};

enum status {
    READY, SENDING, SENT
};

struct request {
    Connection* connection;
    Tipo tipo;
    char url[MAX_DATA_SIZE];
    Status status;
};

Request* createRequest(Connection* connection, Tipo tipo);
void setStatus(Request* request, Status status);
Tipo* getTipo(char* strTipo);
void setUrl(Request* request, char* url);