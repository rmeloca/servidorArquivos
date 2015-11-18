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
};

Request* createRequest(Connection* connection, char* message);