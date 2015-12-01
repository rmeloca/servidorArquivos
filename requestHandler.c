#include <stdlib.h>

#include "header/requestHandler.h"
#include "stdio.h"

void* createRequestHandler(void* args) {
    Connection* connection;
    Request* request;
    Package* replyPackage;

    connection = (Connection*) args;

    //should I merge into a single request?
    request = createRequest(connection, WELCOME);
    setStatus(request, READY);
    addRequest(request);

    request = createRequest(connection, MAXDATASIZE);
    setStatus(request, READY);
    addRequest(request);

    replyPackage = receivePackage(connection);
    request = createRequest(connection, LS);
    setUrl(request, "/");
    setMaxClientDataSize(request, atoi(replyPackage->dados));
    addRequest(request);
    while (1) {
        listenConnection(connection);
    }
    CONN_close(connection);
}

void listenConnection(Connection* connection) {
    Package* package = NULL;
    Package* replyPackage = NULL;
    Request* request = NULL;

    package = receivePackage(connection);

    switch (package->tipo) {
        case LS:
            //askDataSize
            request = createRequest(connection, MAXDATASIZE);
            addRequest(request);
            replyPackage = receivePackage(connection);

            //finalize request
            request = createRequest(connection, LS);
            setUrl(request, package->dados);
            setMaxClientDataSize(request, atoi(replyPackage->dados));
            setStatus(request, READY);
            addRequest(request);
            break;
        case WGET:
            //askDataSize
            request = createRequest(connection, MAXDATASIZE);
            addRequest(request);
            replyPackage = receivePackage(connection);

            //finalize request
            request = createRequest(connection, WGET);
            setUrl(request, package->dados);
            setMaxClientDataSize(request, atoi(replyPackage->dados));
            setStatus(request, READY);
            addRequest(request);
            break;
        case CLOSECONNECTION:
            return;
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