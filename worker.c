#include <stdlib.h>
#include "header/worker.h"

void* listenBuffer(void* args) {
    Package* package = NULL;
    Request* request = NULL;
    char* data;

    while (1) {
        while (isEmptyList(requestBuffer));//sleep while isnt any request to process
        request = getRequest();
        switch (request->tipo) {
            case WELCOME:
                data = "Conexão estabelecida\n";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);

                data = "MRFileServer 0.1\n";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);
                
                data = ".ls [PATH]\n";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);
                
                data = ".wget [FILE]\n";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);
                break;
        }
        free(request);
    }
}

void ls();
void wget();

void sendPackage(Connection* connection, Package* package) {
    CONN_send(connection, (void*) package, sizeof (package), 0);
}