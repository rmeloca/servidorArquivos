#include <stdlib.h>
#include <string.h>
#include "header/package.h"

Package* createPackage(Tipo tipo, char* dados, int tamanhoTotal, int offset) {
    Package* pckg = (Package*) malloc(sizeof (Package));

    pckg->tipo = tipo;
    strcpy(pckg->dados, dados);
    pckg->tamanhoTotal = tamanhoTotal;
    pckg->offset = offset;

    return pckg;
}
