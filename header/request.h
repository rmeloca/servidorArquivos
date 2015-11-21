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
    LS, WGET, WELCOME, MAXPACKAGESIZE, CLOSECONNECTION, OTHER
};

enum status {
    READY, SENDING, SENT
};

struct request {
    Connection* connection;
    Tipo tipo;
    char url[MAX_URL_SIZE];
    Status status;
};

Request* createRequest(Connection* connection, Tipo tipo);
void setStatus(Request* request, Status status);
void setTiDpo(Request* request, Tipo tipo);