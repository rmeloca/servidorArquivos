#pragma once

#include <stdint.h>
#include "connection.h"
#include "server.h"

void* createRequestHandler(void* args);
void listenConnection(Connection* connection);
void interpretarMensagem(Request* request, char* message);