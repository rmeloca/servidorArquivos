#pragma once

#include "package.h"

typedef struct connection_t Connection;

#define MAX_DATA_SIZE 2048

Package* parseInput(char buffer[MAX_DATA_SIZE]);