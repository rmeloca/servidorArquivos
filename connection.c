#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "connection.h"

int CONN_getSocket(connection_t *connection){
    if(!connection){
        fprintf(stderr, "CONN_getSocket: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    return connection->clientSock;
}

char* CONN_getPeerName(connection_t *connection){
    if(!connection){
        fprintf(stderr, "CONN_getPeerName: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    return connection->host;
}

char* CONN_getPeerPort(connection_t *connection){
    if(!connection){
        fprintf(stderr, "CONN_getPeerPort: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }    
    
    return connection->port;
}

connection_t* CONN_connectTo(char* host, char* port){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    int keepAlive = 1;
    connection_t *connection;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    
    s = getaddrinfo(host, port, &hints, &result);
    if(s!= 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    
    for(rp = result; rp != NULL; rp = rp->ai_next){
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        if(sfd == -1)
            continue;
        
        if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; //connected!
        
        close(sfd);
    }
    
    if(rp == NULL){
        fprintf(stderr, "Could not connect :(\n");
        exit(EXIT_FAILURE);
    }
    
    freeaddrinfo(result);
    
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
    
    connection = malloc(sizeof(connection_t));
    
    connection->clientSock = sfd;
    connection->host = malloc(sizeof(char) * NI_MAXHOST + 1);
    connection->port = malloc(sizeof(char) * NI_MAXSERV + 1);
    connection->peerAddr = malloc(sizeof(struct sockaddr));
    connection->peerAddrLen = sizeof(struct sockaddr);        
    
    s = getpeername(sfd, connection->peerAddr, &(connection->peerAddrLen));
    if(s!= 0){
        fprintf(stderr, "getpeername: %s\n", gai_strerror(s));
        return NULL;
    }    
  
    s = getnameinfo(connection->peerAddr, connection->peerAddrLen, connection->host, NI_MAXHOST, connection->port, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);
    if(s!= 0){
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        return NULL;
    }
    
    return connection;
    
    
}

int CONN_listenTo(char* port){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sock, s;
    struct pollfd fds;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    
    s = getaddrinfo(NULL, port, &hints, &result);
    if(s!= 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }    
    
    for(rp = result; rp != NULL; rp = rp->ai_next){
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(sock == -1)
            continue;
        
        int yes=1; 
        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) { 
            perror("setsockopt"); 
            exit(1); 
        }  
        
        if(bind(sock, rp->ai_addr, rp->ai_addrlen) == 0)
            break; //success!
        
        close(sock);
    }
    
    if(rp == NULL){
        fprintf(stderr, "Could not bind!\n");
        exit(EXIT_FAILURE);
    }
    else{
        fprintf(stderr, "socket bound to %zd...\n", rp->ai_addr);
    }    
    
    fcntl(sock, F_SETFD, O_NONBLOCK);
    
    if(listen(sock, 100)){
        perror("listen");
        exit(EXIT_FAILURE);
    }   

    return sock;    
}

connection_t* CONN_accept(int listenSocket){
    int s, newSock;
    struct pollfd fds;
    int keepAlive = 1;
    connection_t* connection;
    
    fds.fd = listenSocket;
    fds.events = POLL_IN;
    fds.revents = 0;    
    
    s = poll(&fds, 1, -1);
        
    if(fds.revents & POLL_IN){

        connection = malloc(sizeof(connection_t));
        connection->host = malloc(sizeof(char) * NI_MAXHOST + 1);
        connection->port = malloc(sizeof(char) * NI_MAXSERV + 1);
        connection->peerAddr = malloc(sizeof(struct sockaddr));
        connection->peerAddrLen = sizeof(struct sockaddr);
        
        do{
            newSock = accept(fds.fd, connection->peerAddr, &(connection->peerAddrLen));
        }while((newSock == EAGAIN) || (newSock == EWOULDBLOCK));
        
        s = getnameinfo(connection->peerAddr, connection->peerAddrLen, connection->host, NI_MAXHOST, connection->port, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);            

        fprintf(stderr, "connected to %s:%s...\n", connection->host, connection->port);

        connection->clientSock = newSock;
        setsockopt(newSock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
              
        return connection;
        
    }
    else{
        fprintf(stderr, "(%d) listen error: incorrect poll event\n", __LINE__);
        return NULL;
    }
    
}

//flags in man sendto
int CONN_send(connection_t* connection, void* buffer, int bufferLen, int flags){
    int s;
    
    if(!connection){
        fprintf(stderr, "CONN_send: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    s = sendto(connection->clientSock, buffer, bufferLen, flags, connection->peerAddr, connection->peerAddrLen);
    if(s == -1){
        perror("sendto");
    }
    return s;
}

int CONN_receive(connection_t* connection, void* buffer, int bufferLen, int flags){
    struct pollfd fds;
    int s;
    
    if(!connection){
        fprintf(stderr, "CONN_receive: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    fds.events = POLL_IN;
    fds.fd = connection->clientSock;
    fds.revents = 0;
    
    s = poll(&fds, 1, -1);
    if(s == -1){
        perror("poll");
    }
    
    s = recv(fds.fd, buffer, bufferLen, flags);
    if(s == -1){
        perror("recv");
    }
    
    return s;
}

void CONN_close(connection_t* connection){
    
    if(!connection){
        fprintf(stderr, "CONN_close: not connected! (connection = NULL)\n");
        exit(EXIT_FAILURE);
    }
    
    close(connection->clientSock);
    free(connection->host);
    free(connection->port);
    free(connection->peerAddr);
    free(connection);
}