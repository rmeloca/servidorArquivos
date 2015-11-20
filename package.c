#include <stdio.h>
#include <header/package.h>

Package* createPackage(Tipo tipo, char* dados ,int tamanhoTotal, int offset){
    Package* pckg = (Package*) malloc(sizeof(Package));

    pckg->tipo = tipo;
    pckg->dados = dados;
    pckg->tamanhoTotal = tamanhoTotal;
    pckg->offset = offset;

    return pckg;
}
