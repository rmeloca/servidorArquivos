#pragma once

#include "package.h"
#include "server.h"

/**
 * Método que cada Thread Worker executa. Escuta o buffer compartilhado e obtém requisições para processá-las
 * @param args Objeto necessário pela biblioteca pthread.h
 * @return Objeto necessário pela biblioteca pthread.h 
 */
void* listenBuffer(void* args);
void ls();
void wget();

/**
 * Cria uma abstração para o envio de pacotes. Envia os pacotes através da conexão.
 * @param connection Conexão entre o cliente e o servidor
 * @param package Pacote devidamente populado
 */
void sendPackage(Connection* connection, Package* package);