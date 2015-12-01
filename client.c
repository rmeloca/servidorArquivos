#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <linux/limits.h>
#include "header/client.h"

int main(int argc, char** argv) {
    qtdWget = 0;
    aux = 1;
    //Conexão ao cliente
    Connection* connection;

    //host do servidor e a porta a conectar
    char* host;
    char* port;

    //Buffer usado para receber e enviar dados
    Package* buffer = NULL;
    char packageStr[sizeof (Package)];
    char bufferStr[MAX_DATA_SIZE];
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
    buffer = (Package*) packageStr;

    CONN_receive(connection, packageStr, sizeof (Package), 0);
    packageDeals(connection, buffer);

    CONN_receive(connection, packageStr, sizeof (Package), 0);
    packageDeals(connection, buffer);

    CONN_receive(connection, packageStr, sizeof (Package), 0);
    packageDeals(connection, buffer);

    CONN_receive(connection, packageStr, sizeof (Package), 0);
    packageDeals(connection, buffer);

    CONN_receive(connection, packageStr, sizeof (Package), 0);
    packageDeals(connection, buffer);

    while (1) {
        while (aux) {
            aux = 0;
            CONN_receive(connection, packageStr, sizeof (Package), 0);
            //            buffer = (Package*) packageStr;
            packageDeals(connection, buffer);
            //            free(buffer);
            //            CONN_receive(connection, packageStr, sizeof (Package), 0);
            //            packageDeals(connection, buffer);
        }

        printf("Digite uma mensagem para o servidor: ");

        //ler a mensagem a ser enviada ao servidor
        fgets(bufferStr, MAX_DATA_SIZE, stdin);

        //subtituir \n por um terminador de string
        *(strstr(bufferStr, "\n")) = 0;

        //ter certeza que há um terminador de string no último caractere
        bufferStr[MAX_DATA_SIZE - 1] = 0;

        //enviar a mensagem
        parseInput(connection, bufferStr);

        //verificar se enviou um "sair". Caso afirmativo, terminar o cliente.
        if (!strcmp(bufferStr, "sair")) {
            break;
        }
    }

    //fechar a conexão
    CONN_close(connection);

    return EXIT_FAILURE;

}

void packageDeals(Connection* connection, Package* pckg) {
    if (pckg->tipo == WELCOME) {
        printf("%s\n", pckg->dados);
    } else if (pckg->tipo == LS) {
        if (pckg->offset > (pckg->tamanhoTotal / MAX_DATA_SIZE)) {
        }
        printf("%s\n", pckg->dados);
    } else if (pckg->tipo == WGET) {
        wgetDeals(connection, pckg);
    } else if (pckg->tipo == MAXDATASIZE) {
        aux = 1;
        char c[MAX_DATA_SIZE] = "2048";
        //        sprintf(c, "%d", MAX_DATA_SIZE);
        //        strcat(c, "\0");
        printf("MAX_DATA_SIZE enviado\n");
        sendPackage(connection, pckg->tipo, c);
    } else if (pckg->tipo == FILENOTEXIST) {
        printf("Arquivo solicitado não exite\n");
    } else if (pckg->tipo == CLOSECONNECTION) {
        //Encerrar conexao
        printf("%s\n", pckg->dados);
    } else if (pckg->tipo == OTHER) {
        //---
    }
}

void wgetDeals(Connection connection, Package* pckg) {
    char nomeArq[23] = "Arquivo_";
    char numArq[3];
    sprintf(numArq, "%d", qtdWget);
    strcat(nomeArq, numArq);
    FILE* file = fopen(nomeArq, "w+");
    int tamParte = ((pckg->tamanhoTotal) / MAX_DATA_SIZE);
    int seek = MAX_DATA_SIZE * pckg->offset;
    fseek(file, 0, seek);
    fwrite(&(pckg->dados), MAX_DATA_SIZE, 1, file);
    fclose(file);
    sendPackage(connection, OTHER, "ACK");
    if (pckg->offset < tamParte) {
        aux = 1;
    } else {
        printf("Download concluido");
        qtdWget++;
    }
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
    int i = 0;
    char tipo[MAX_DATA_SIZE] = "";
    char dados[MAX_DATA_SIZE] = "";

    while (i < MAX_DATA_SIZE) {
        if (buffer[i] == ' ') {
            aux = i;
            break;
        }
        i++;
    }
    if (i < MAX_DATA_SIZE) {
        memcpy(&tipo, &buffer[0], i);
        memcpy(&dados, &buffer[i + 1], (MAX_DATA_SIZE - i));

        Tipo t = getTipo(tipo);
        sendPackage(connection, t, dados);

    }
}
