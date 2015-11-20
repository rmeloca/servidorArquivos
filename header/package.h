#pragma once

#include "string.h"
#include "request.h"

typedef struct package Package;


struct package {
    Tipo tipo;
    char dados[MAX_DATA_SIZE];
    int tamanhoTotal;
    int offset;
};

Package* createPackage(Tipo tipo, char* buffer,int tamanhoTotal, int offset);
