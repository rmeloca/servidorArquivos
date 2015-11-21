#pragma once

#include "package.h"
#include "server.h"

void* listenBuffer(void* args);
void ls();
void wget();
void sendPackage(Connection* connection, Package* package);