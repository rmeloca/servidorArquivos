#pragma once

#include "connection.h"
#include "listDynamic.h"
#include "requestHandler.h"

typedef struct connection_t Connection;

List* requestBuffer;

int addRequest(Request* request);
Request* getRequest();
void dispatcher(int listenSock, char* port);