#pragma once

#include "connection.h"

typedef struct package Package;
typedef enum tipo Tipo;

/**
 * Limite de dados que os pacotes comportam
 */
#define MAX_DATA_SIZE 2048

/**
 * Enum que codifica os tipos de requisição atendidas e pacotes enviados
 */
enum tipo {
    LS, WGET, WELCOME, MAXDATASIZE, FILENOTEXIST, CLOSECONNECTION, OTHER
};

/**
 * Objeto a trafegar pela conexão. Esta estrutura é responsável por fazer interface com o cliente e servidor
 * O cliente envia um pacote para o servidor e o servidor responde com outro pacote
 */
struct package {
    Tipo tipo; //Tipo do pacote
    char dados[MAX_DATA_SIZE]; //Dados que o pacote transporta. Possui tamanho fixo
    int tamanhoTotal; //Tamanho total dos dados. Se o número exceder MAX_DATA_SIZE, então, o pacote está fragmentado
    int offset; //Posição do pacote (fragmento) no montante enviado.
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

/**
 * Dado uma string, codifica-o para um Tipo e o retorna.
 * @param strTipo
 * @return 
 */
Tipo getTipo(char* strTipo);