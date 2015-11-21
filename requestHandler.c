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
    //    uint8_t buffer[MAX_URL_SIZE];
    Package* package;
    CONN_receive(connection, package, sizeof (Package), 0);
    printf("recebi '%s' do cliente (%s:%s)... (len = %zd)\n", package, CONN_getPeerName(connection), CONN_getPeerPort(connection), sizeof (Package));
    /*switch package->tipo{
        case LS:
            
    }*/
    if (package->tipo == LS) {
        //Parse path
        //Listar arquivos
    } else if (package->tipo == CLOSECONNECTION) {
        return;
    }
}