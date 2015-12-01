#include <stdlib.h>
#include <string.h>
#include "header/package.h"
#include "header/client.h"

Package* createPackage(Tipo tipo, char* dados, int tamanhoTotal, int offset) {
    Package* pckg = (Package*) malloc(sizeof (Package));

    pckg->tipo = tipo;
    memcpy(pckg->dados, dados, MAX_DATA_SIZE);
    pckg->tamanhoTotal = tamanhoTotal;
    pckg->offset = offset;

    return pckg;
}

Tipo getTipo(char* strTipo) {
    if (!strcmp(strTipo, "welcome")) {
        return WELCOME;
    } else if (!(strcmp(strTipo, "ls"))) {
        return LS;
    } else if (!strcmp(strTipo, "wget")) {
        return WGET;
    } else if (!strcmp(strTipo, "maxdatasize")) {
        return MAXDATASIZE;
    } else if (!strcmp(strTipo, "filenoexist")) {
        return FILENOTEXIST;
    } else if (!strcmp(strTipo, "closeconection")) {
        return CLOSECONNECTION;
    } else {
        return OTHER;
    }
}