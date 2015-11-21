#include "header/requestHandler.h"
#include "stdio.h"

void* createRequestHandler(void* args) {
    Connection* connection;
    Request* request;

    connection = (Connection*) args;

    request = createRequest(connection, WELCOME);
    addRequest(request);
    request = createRequest(connection, LS);
    addRequest(request);

    while (1) {
        listenConnection(connection);
    }
    CONN_close(connection);
}

void listenConnection(Connection* connection) {
    Package* package = NULL;
    Request* request = NULL;

    CONN_receive(connection, package, sizeof (Package), 0);
    printf("recebi '%s' do cliente (%s:%s)... (len = %zd)\n", package->dados, CONN_getPeerName(connection), CONN_getPeerPort(connection), sizeof (Package));
    switch (package->tipo) {
        case LS:
            request = createRequest(connection, LS);
            setUrl(request, package->dados);
            setStatus(request, READY);
            break;
        case WGET:
            break;
        case CLOSECONNECTION:
            return;
            break;
    }
    addRequest(request);
}