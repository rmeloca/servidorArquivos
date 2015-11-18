#pragma once

#include "connection.h"

void* createRequestHandler(void* args);
void listenConnection(Connection* connection);