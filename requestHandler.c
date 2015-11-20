#include "header/requestHandler.h"
#include "stdio.h"

void* createRequestHandler(void* args) {
    Connection* connection;
    Request* request;
    char* initialMessage;

    connection = (Connection*) args;

    initialMessage = "Conexão estabelecida\n";
    request = createRequest(connection, NONE, initialMessage);
    addRequest(request);
    initialMessage = "MRFileServer 0.1\n";
    request = createRequest(connection, NONE, initialMessage);
    addRequest(request);
    initialMessage = ".ls [PATH]\n";
    request = createRequest(connection, NONE, initialMessage);
    addRequest(request);
    initialMessage = ".wget [FILE]\n";
    request = createRequest(connection, NONE, initialMessage);
    addRequest(request);
    initialMessage = "/\n";
    request = createRequest(connection, LS, initialMessage);
    addRequest(request);

    while (1) {
        listenConnection(connection);
    }
    CONN_close(connection);
}

void listenConnection(Connection* connection) {
    //    uint8_t buffer[MAX_URL_SIZE];
    char buffer[MAX_URL_SIZE]; //url + espaco + wget
    CONN_receive(connection, buffer, MAX_URL_SIZE, 0);
    printf("recebi '%s' do cliente (%s:%s)... (len = %zd)\n", buffer, CONN_getPeerName(connection), CONN_getPeerPort(connection), strlen(buffer));

    if (buffer[0] == 'l' && buffer[1] == 's') {
        //Parse path
        //Listar arquivos
    }

    if (!strcmp(buffer, "sair")) {
        return;
    }
}

void interpretarMensagem(Request* request, char* message) {
    if (message[0] == 'l' && message[1] == 's') {
        setTipo(request, LS);

    } else if (message != NULL) {

    }
    //split in space
}
