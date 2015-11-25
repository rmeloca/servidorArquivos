#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <linux/limits.h>
#include "header/client.h"

int main(int argc, char** argv) {
    qtdWget = -1;
    //Conexão ao cliente
    Connection* connection;

    //host do servidor e a porta a conectar
    char* host;
    char* port;

    //Buffer usado para receber e enviar dados
    Package* buffer;
    char* bufferStr;
    //Verificar se a porta e o host foi passado como argumento
    if (argc < 3) {
        fprintf(stderr, "uso: %s host porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Host é o primeiro argumento e porta o segundo.
    host = argv[1];
    port = argv[2];

    //Conectar ao servidor
    connection = CONN_connectTo((char*) host, (char*) port);

    //verificar se houve sucesso na conexão
    if (!connection) {
        fprintf(stderr, "Não foi possível conectar a %s:%s!\n", host, port);
        return (EXIT_FAILURE);
    }

    //Aguardar a mensagem de boas vindas e imprimi-la
    CONN_receive(connection, buffer, sizeof (Package), 0);
    if (buffer->tipo == LS);
    printf("%s\n", buffer->dados);

    while (1) {
        printf("Digite uma mensagem para o servidor: ");

        //ler a mensagem a ser enviada ao servidor
        fgets(bufferStr, MAX_DATA_SIZE, stdin);

        //subtituir \n por um terminador de string
        *(strstr(bufferStr, "\n")) = 0;

        //ter certeza que há um terminador de string no último caractere
        bufferStr[MAX_DATA_SIZE - 1] = 0;


        //enviar a mensagem
        parseInput(connection, bufferStr);

        //aguardar o echo
        CONN_receive(connection, buffer, MAX_DATA_SIZE, 0);
        packageDeals(connection, buffer);

        //verificar se enviou um "sair". Caso afirmativo, terminar o cliente.
        if (!strcmp(buffer, "sair")) {
            break;
        }
    }

    //fechar a conexão
    CONN_close(connection);

    return EXIT_FAILURE;

}

void packageDeals(Connection* connection, Package* pckg) {
    if (pckg->tipo == WELCOME) {
        printf("%s", &pckg->dados);

    } else if (pckg->tipo == LS) {
        printf("%s", &pckg->dados);

    } else if (pckg->tipo == WGET) {
        wgetDeals(pckg);
    } else if (pckg->tipo == MAXDATASIZE) {
        //send
    } else if (pckg->tipo == FILENOTEXIST) {
        printf("Arquivo solicitado não exite");
    } else if (pckg->tipo == CLOSECONNECTION) {
        //Encerrar conexao
        printf("%s", &pckg->dados);
    } else if (pckg->tipo == OTHER) {
        //---
    }
}

void wgetDeals(Package* pckg) {
    char nomeArq[23] = "Arquivo_";
    char numArq[3];
    sprintf(numArq, "%d", qtdWget);
    strcat(nomeArq, numArq);
    FILE* file = fopen(nomeArq, "w+");
    int tamParte = pckg->tamanhoTotal / MAX_DATA_SIZE;
    int seek = tamParte * pckg->offset;
    fseek(file, 0, seek);
    fwrite(&(pckg->dados), sizeof (char), sizeof (pckg->dados), file);
    fclose(file);
}

void sendPackage(Connection* connection, Tipo tipo, char* dados) {
    if (tipo == LS) {
        Package* package = createPackage(tipo, dados, strlen(dados), 0);
        CONN_send(connection, package, sizeof (Package), 0);

    } else if (tipo == WGET) {
        Package* package = createPackage(tipo, dados, strlen(dados), 0);
        qtdWget++;
        CONN_send(connection, package, sizeof (Package), 0);

    } else if (tipo == MAXDATASIZE) {
        char d[10];
        sprintf(d, "%d", MAX_DATA_SIZE);
        Package* package = createPackage(tipo, d, 10, 0);
        CONN_send(connection, package, sizeof (Package), 0);
    } else if (tipo == CLOSECONNECTION) {
        Package* package = createPackage(tipo, dados, strlen(dados), 0);
        CONN_send(connection, package, sizeof (Package), 0);

    } else if (tipo == OTHER) {
        //---
    }
}

void parseInput(Connection* connection, char buffer[MAX_DATA_SIZE]) {
    Package* pckg;
    int i = 0, aux = 0;
    char tipo[MAX_DATA_SIZE];
    char dados[MAX_DATA_SIZE];

    while (i < MAX_DATA_SIZE) {
        if (buffer[i] == ' ') {
            aux = i;
            break;
        }
    }
    memcpy(tipo, &buffer, i);
    memcpy(dados, &buffer[i + 1], (MAX_DATA_SIZE - i));
    Tipo t = getTipo(tipo);
    sendPackage(connection, t, dados);
}