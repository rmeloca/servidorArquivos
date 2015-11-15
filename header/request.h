#pragma once

#include "string.h"
#include "server.h"

typedef struct request Request;

struct request {
    Connection* connection;
    char* message;
};

Request* createRequest(Connection* connection, char* message);