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
    if (strcmp(strTipo, "WELCOME")) {
        return WELCOME;
    } else if (strcmp(strTipo, "LS")) {
        return LS;
    } else if (strcmp(strTipo, "WGET")) {
        return WGET;
    } else if (strcmp(strTipo, "MAXDATASIZE")) {
        return MAXDATASIZE;
    } else if (strcmp(strTipo, "FILENOTEXIST")) {
        return FILENOTEXIST;
    } else if (strcmp(strTipo, "CLOSECONNECTION")) {
        return CLOSECONNECTION;
    } else if (strcmp(strTipo, "OTHER")) {
        return OTHER;
    }
    return OTHER;
}