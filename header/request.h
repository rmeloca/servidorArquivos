#pragma once

#include "string.h"
#include "server.h"

typedef struct request Request;
typedef struct tipo Tipo;
typedef struct status Status;

#define MAX_URL_SIZE 2048
#define MAX_DATA_SIZE 2048

struct request {
    Connection* connection;
    char url[MAX_URL_SIZE];
    Tipo tipo;
    Status status;
    char dados[MAX_DATA_SIZE];
};

enum tipo{
    
};

enum status{
    
};

Request* createRequest(Connection* connection, char* message);