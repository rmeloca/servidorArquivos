#include <stdlib.h>
#include <dirent.h>
#include "header/worker.h"

void* listenBuffer(void* args) {
    Package* package = NULL;
    Request* request = NULL;
    char* data;

    while (1) {
        request = getRequest();//sleep while isnt any request to process
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

                //LS

                break;
        }
        free(request);
    }
}

void ls(char* url) {
    DIR *dir;
    struct dirent *lsdir;

    dir = opendir(url);

    /* print all the files and directories within directory */
    while ((lsdir = readdir(dir)) != NULL) {
        printf("%s\n", lsdir->d_name);
    }
    closedir(dir);
}

void wget();

void sendPackage(Connection* connection, Package* package) {
    CONN_send(connection, (void*) package, sizeof (package), 0);
    free(package);
}