#pragma once

#include "package.h"

typedef struct connection_t Connection;

#define MAX_DATA_SIZE 2048

int qtdWget;
int aux;
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
void packageDeals(Connection* connection, Package* pckg);
void wgetDeals(Connection* connection, Package* pckg);
void sendPackage(Connection* connection, Tipo tipo, char* dados);
void parseInput(Connection* connection, char buffer[MAX_DATA_SIZE]);