#pragma once

#include <stdint.h>
#include "server.h"
#include "package.h"

/**
 * Método que cada Thread Produtora de requisições (requestHandler) utiliza para atendender os clientes
 * Envia pacotes de boas-vindas para o cliente e o escuta
 * @param args Objeto do tipo Connection
 * @return Objeto nulo. Thread.create() exige retorno de um Objeto
 */
void* createRequestHandler(void* args);

/**
 * Distingue as responsabilidades do Objeto RequestHandler
 * Escuta o cliente, interpreta o pacote recebido, transforma-o em Requisição
 * e adiciona-o no buffer compartilhado.
 * Para requisições do tipo WGET, prepara uma requisição do tipo MAXDATASIZE
 * @param connection Conexão entre o cliente e o servidor
 */
void listenConnection(Connection* connection);

/**
 * Cria uma abstração para recebimento de pacotes
 * @param connection Conexão entre o cliente e o servidor
 * @return Pacote recebido do cliente
 */
Package* receivePackage(Connection* connection);

/**
 * Pergunta ao cliente qual o tamanho máximo de pacote que ele suporta
 * @param connection
 * @return 
 */
int askMaxClientDataSize(Connection* connection);