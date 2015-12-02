#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <pthread.h>
#include "header/worker.h"

void* listenBuffer(void* args) {
    Package* package = NULL;
    Request* request = NULL;
    char* data;

    while (1) {
        request = getRequest(); //sleep while isnt any request to process

        pthread_mutex_lock(request->count_mutex);

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

        pthread_cond_signal(request->count_threshold_cv);
        pthread_mutex_unlock(request->count_mutex);
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
    Package* package;
    int tamanho;
    int offset = 0;
    char* url = getAbsolutePath(request->url);
    file = fopen(url, "r");

    if (file != NULL) {
        //Vai para ultima posicao do arquivo
        fseek(file, 0, SEEK_END);
        // pega a posição corrente de leitura no arquivo
        tamanho = ftell(file);
        fseek(file, 0, 0);

        char data[2048];
        while ((offset * request->maxClientDataSize) < tamanho) {
            fread(data, 1, 2048, file);
            package = createPackage(WGET, data, tamanho, offset);
            sendPackage(request->connection, package);
            offset++;
            receivePackage(request->connection);

        }
    }
}

void sendPackage(Connection* connection, Package * package) {
    CONN_send(connection, package, sizeof (Package), 0);
    free(package);
}