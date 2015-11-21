#pragma once

#include <stdint.h>
#include "server.h"
#include "package.h"

void* createRequestHandler(void* args);
void listenConnection(Connection* connection);
Package* receivePackage(Connection* connection);