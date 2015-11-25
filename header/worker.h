#pragma once

#include "package.h"
#include "server.h"

/**
 * Método que cada Thread Worker executa. Escuta o buffer compartilhado e obtém requisições para processá-las
 * @param args Objeto necessário pela biblioteca pthread.h
 * @return Objeto necessário pela biblioteca pthread.h 
 */
void* listenBuffer(void* args);

/**
 * Método obtido de outras fontes. Adaptado para concatenar a saída e retorná-la
 * http://www.hardware.com.br/comunidade/arquivos-varrer/1103524/
 * @param url caminho absoluto do diretório
 * @return resultado concatenado
 */
char* ls(char* url);

/**
 * Converte um caminho relativo em absoluto
 * @param relativePath
 * @return 
 */
char* getAbsolutePath(char* relativePath);

/**
 * Responsável por enviar a requisição LS em multi-parting
 * @param request
 * @param data
 */
void sendLS(Request* request);

/**
 * Envia a requisição WGET via multi-parting
 * @param request
 */
void sendWGET(Request* request);

/**
 * Cria uma abstração para o envio de pacotes. Envia os pacotes através da conexão.
 * @param connection Conexão entre o cliente e o servidor
 * @param package Pacote devidamente populado
 */
void sendPackage(Connection* connection, Package* package);