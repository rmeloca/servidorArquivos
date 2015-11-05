#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "connection.h"

#define BUFFER_SIZE 1024

int main(int argc, char** argv){

    //Socket usado para aguardar a conexão
    int listenSock;
    
    //Conexão ao cliente
    connection_t* connection;
    
    //Buffer usado para receber e enviar echo
    uint8_t buffer[BUFFER_SIZE];
    
    //Porta a ser usada pelo servidor... (use portas altas (10000+) para evitar conflitos com serviços já sendo executados)
    char* port;
    
    //Verficar se a porta foi passada como argumento
    if(argc < 2){
        fprintf(stderr, "uso: %s porta\n", argv[0]);
        return EXIT_FAILURE;
    }

    //porta é o primeiro argumento
    port = argv[1];    

    //Abrir socket para arguardar conexões
    listenSock = CONN_listenTo((char*)port);
    
    //Aceitar conexões. Esta função retorna uma conexão (usando um novo socket) ou NULL.
    //listenSocket ainda pode ser chamado para aceitar outras conexões!
    connection = CONN_accept(listenSock);
  
    //Verificar se houve sucesso ao conectar
    if(!connection){
        fprintf(stderr, "Não foi possível conectar ao cliente remoto na porta %s!\n", port);
        return(EXIT_FAILURE);
    }
    
    //Enviar uma mensagem de boas-vindas ao cliente
    const char* hello = "Servidor Echo v0.01 -- Bem Vindo(a)!";
    CONN_send(connection, (void*)hello, strlen(hello), 0);
    
    //A ideia de um servidor echo é simplesmente mandar de volta a mensagem recebida
    while(1){
        //aguardar a mensagem
        CONN_receive(connection, buffer, BUFFER_SIZE, 0);

        //imprimir a mensagem recebida e o tamanho da mensagem
        printf("recebi '%s' do cliente... (len = %d)\n", buffer, strlen(buffer));
        
        //enviar de volta a mensagem recebida.
        CONN_send(connection, buffer, strlen(buffer)+1, 0);
        
        //detectar se a mensagem "sair" foi enviada.. se sim, fechar o servidor
        if(!strcmp(buffer, "sair")){
            break;
        }
    }
    
    //fechar a conexão
    CONN_close(connection);
    
    //fechar o socket
    close(listenSock);
    
    return EXIT_FAILURE;
    
}

