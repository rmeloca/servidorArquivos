#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "header/worker.h"

void* listenBuffer(void* args) {
    Package* package = NULL;
    Request* request = NULL;
    char* data;

    while (1) {
        request = getRequest(); //sleep while isnt any request to process
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
            case LS:
                sendLS(request);
                break;
            case WGET:
                sendWGET(request);
                break;
        }
        free(request);
    }
}

char* ls(char* url) {
    char* retorno;
    DIR *dir;
    struct dirent *lsdir;

    dir = opendir(url);

    /* print all the files and directories within directory */
    while ((lsdir = readdir(dir)) != NULL) {
        printf("%s\n", lsdir->d_name);
        strcat(retorno, lsdir->d_name);
    }
    closedir(dir);
    return retorno;
}

char* getAbsolutePath(char* relativePath) {
    char* data;
    data = "./server";
    strcat(data, relativePath);
    return data;
}

void sendLS(Request* request) {
    Package* package;
    char* data;

    data = ls(getAbsolutePath(request->url));
    package = createPackage(LS, data, strlen(data), 0);
    sendPackage(request->connection, package);
}

void sendWGET(Request* request) {
    FILE* file;
    char* data;//void*
    Package* package;

    file = fopen(getAbsolutePath(request->url), "rb");

    fread(data, sizeof (char), request->maxClientDataSize, file);//void
    fseek(file, 6, SEEK_SET);
    package = createPackage(LS, data, strlen(data), 0);
    sendPackage(request->connection, package);
}

void sendPackage(Connection* connection, Package* package) {
    CONN_send(connection, (void*) package, sizeof (package), 0);
    free(package);
}