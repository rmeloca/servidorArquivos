#include <stdlib.h>

#include "header/requestHandler.h"
#include "stdio.h"

void* createRequestHandler(void* args) {
    Connection* connection;
    Request* request;
    int maxClientDataSize;

    connection = (Connection*) args;

    //should I merge into a single request?
    request = createRequest(connection, WELCOME);
    setStatus(request, READY);
    addRequest(request);

    //to send ls
    maxClientDataSize = askMaxClientDataSize(connection);

    //finalize request
    request = createRequest(connection, LS);
    setUrl(request, "/");
    setMaxClientDataSize(request, maxClientDataSize);
    addRequest(request);
    while (1) {
        request->count_mutex = malloc();
        request->count_mutex = malloc();
        
        //malloc  init
        listenConnection(connection);
        //lock cond destroy
    }
    CONN_close(connection);
}

void listenConnection(Connection* connection) {
    Package* package = NULL;
    Request* request = NULL;
    int maxClientDataSize;
    char* url;
    Tipo tipo;

    package = receivePackage(connection);
    strcpy(url, package->dados);
    tipo = package->tipo;
    maxClientDataSize = askMaxClientDataSize(connection);

    //finalize request
    switch (tipo) {
        case LS:
            request = createRequest(connection, LS);
            setUrl(request, url);
            setMaxClientDataSize(request, maxClientDataSize);
            setStatus(request, READY);
            break;
        case WGET:
            //finalize request
            request = createRequest(connection, WGET);
            setUrl(request, url);
            setMaxClientDataSize(request, maxClientDataSize);
            setStatus(request, READY);
            break;
        case CLOSECONNECTION:
            return;
            break;
        default:
            request = createRequest(connection, OTHER);
            setStatus(request, READY);
            break;
    }
    addRequest(request);
}

Package* receivePackage(Connection* connection) {
    Package* package = NULL;
    char packageStr[sizeof (Package)];
    CONN_receive(connection, packageStr, sizeof (Package), 0);
    package = (Package*) packageStr;
    printf("recebi '%s' do cliente (%s:%s)... (len = %zd)\n", package->dados, CONN_getPeerName(connection), CONN_getPeerPort(connection), sizeof (Package));
    return package;
}

int askMaxClientDataSize(Connection* connection) {
    Request* request = NULL;
    Package* package = NULL;

    request = createRequest(connection, MAXDATASIZE);
    addRequest(request);
    package = receivePackage(connection);
    return atoi(package->dados);
}