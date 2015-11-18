#pragma once

#include "listDynamic.h"
#include "requestHandler.h"

List* requestBuffer;

int addRequest(Request* request);
Request* getRequest();
int dispatcher(int* listenSock, char* port);