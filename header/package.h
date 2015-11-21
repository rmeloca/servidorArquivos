#pragma once

#include "request.h"
#include "connection.h"

typedef struct package Package;

struct package {
    Tipo tipo;
    char dados[MAX_DATA_SIZE];
    int tamanhoTotal;
    int offset;
};

/**
 * Construtor de cada pacote assume todos os parâmetros, uma vez que ou eles estão completos, ou o pacote não existe.
 * @param tipo tipo do pacote
 * @param bytes a serem gravados no pacote
 * @param tamanhoTotal tamanho total do dado a ser transmitido. Releva se o pacote está fragmentado, quando o número exceder 2048.
 * @param offset deslocamento do pacote em relação ao tamanho total.
 * @return referência para um pacote devidamente alocado em memória.
 */
Package* createPackage(Tipo tipo, char* dados, int tamanhoTotal, int offset);
