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
                data = "Conexão estabelecida";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);

                data = "MRFileServer 0.1";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);

                data = ".ls [PATH]";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);

                data = ".wget [FILE]";
                package = createPackage(WELCOME, data, strlen(data), 0);
                sendPackage(request->connection, package);
                break;
            case LS:
                sendLS(request);
                break;
            case WGET:
                sendWGET(request);
                break;
            case MAXDATASIZE:
                data = "";
                package = createPackage(MAXDATASIZE, data, strlen(data), 0);
                sendPackage(request->connection, package);
                break;
            case OTHER:
                data = "";
                package = createPackage(OTHER, data, strlen(data), 0);
                sendPackage(request->connection, package);
                break;
            case FILENOTEXIST:
                data = "";
                package = createPackage(FILENOTEXIST, data, strlen(data), 0);
                sendPackage(request->connection, package);
                break;
            case CLOSECONNECTION:
                return package;
                break;
        }
        free(request);
    }
}

char* ls(char* url) {
    DIR *dir;
    struct dirent lsdir;
    struct dirent *res = NULL;
    dir = opendir(url);

    char * ret = malloc(sizeof (char) * MAX_DATA_SIZE);
    ret[0] = 0;

    /* print all the files and directories within directory */
    readdir_r(dir, &lsdir, &res);
    while (res != NULL) {
        //        printf("%s\n", (*res)->d_name);
        strcat(ret, (res)->d_name);
        strcat(ret, "\n");
        readdir_r(dir, &lsdir, &res);
    }
    closedir(dir);
    return ret;
}

char* getAbsolutePath(char* relativePath) {
    char* data = (char*) calloc(MAXDATASIZE, sizeof (char));
    strcpy(data, "./files");
    strcat(data, relativePath);
    return data;
}

void sendLS(Request* request) {
    Package* package;
    char* data = "";

    data = ls(getAbsolutePath(request->url));
    package = createPackage(LS, data, strlen(data), 0);
    sendPackage(request->connection, package);
}

void sendWGET(Request* request) {
    FILE* file;
    char* data = "";
    Package* package;

    file = fopen(getAbsolutePath(request->url), "rb");

    if (file != NULL) {
        fread(data, sizeof (char), request->maxClientDataSize, file); //void
        //        fseek(file, request->maxClientDataSize, SEEK_CUR);
    }
    package = createPackage(WGET, data, strlen(data), 0);
    sendPackage(request->connection, package);
}

void sendPackage(Connection* connection, Package* package) {
    CONN_send(connection, package, sizeof (Package), 0);
    free(package);
}