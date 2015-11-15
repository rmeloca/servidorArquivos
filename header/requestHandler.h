#pragma once

#include "connection.h"


#define MESSAGE_SIZE 2048

void* createRequestHandler(void* args);
void listenConnection(Connection* connection);