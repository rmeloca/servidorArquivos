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
    } else if (strcmp(strTipo, "other")) {
        return OTHER;
    }
    return OTHER;
}