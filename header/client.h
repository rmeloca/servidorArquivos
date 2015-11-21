#pragma once

#include "package.h"

typedef struct connection_t Connection;

#define MAX_DATA_SIZE 2048

/**
 * Estabelece conexao com o servidor a partir dos argumentos e aguarda entradas do usuário
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv);

/**
 * Processa a entrada do usuário e retorna um pacote correspondente
 * @param buffer entrada
 * @return um Pacote alocado e populado
 */
Package* parseInput(char buffer[MAX_DATA_SIZE]);