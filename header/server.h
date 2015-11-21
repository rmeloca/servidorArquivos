#pragma once

#include "listDynamic.h"
#include "requestHandler.h"
#include "worker.h"

typedef pthread_t Thread;

List* requestBuffer;

int addRequest(Request* request);
Request* getRequest();
int dispatcher(int* listenSock, char* port);