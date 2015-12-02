#include <stdlib.h>
#include <pthread.h>

#include "header/requestHandler.h"
#include "stdio.h"

void* createRequestHandler(void* args) {
    Connection* connection;
    Request* request;
    int maxClientDataSize;

    connection = (Connection*) args;

    request = createRequest(connection, WELCOME);

    request->count_mutex = malloc(sizeof (pthread_mutex_t));
    request->count_threshold_cv = malloc(sizeof (pthread_cond_t));
    pthread_cond_init(request->count_threshold_cv, NULL);
    pthread_mutex_init(request->count_mutex, NULL);
    pthread_mutex_lock(request->count_mutex);

    setStatus(request, READY);
    addRequest(request);

    pthread_cond_wait(request->count_threshold_cv, request->count_mutex);

    pthread_mutex_unlock(request->count_mutex);
    pthread_cond_destroy(request->count_threshold_cv);
    pthread_mutex_destroy(request->count_mutex);

    //to send ls
    maxClientDataSize = askMaxClientDataSize(connection);

    //finalize request
    request = createRequest(connection, LS);

    request->count_mutex = malloc(sizeof (pthread_mutex_t));
    request->count_threshold_cv = malloc(sizeof (pthread_cond_t));
    pthread_cond_init(request->count_threshold_cv, NULL);
    pthread_mutex_init(request->count_mutex, NULL);
    pthread_mutex_lock(request->count_mutex);

    setUrl(request, "/");
    setMaxClientDataSize(request, maxClientDataSize);
    addRequest(request);

    pthread_cond_wait(request->count_threshold_cv, request->count_mutex);

    pthread_mutex_unlock(request->count_mutex);
    pthread_cond_destroy(request->count_threshold_cv);
    pthread_mutex_destroy(request->count_mutex);

    while (1) {
        listenConnection(connection);
    }
    CONN_close(connection);
}

void listenConnection(Connection* connection) {
    Package* package = NULL;
    Request* request = NULL;
    int maxClientDataSize;
    char* url;
    Tipo tipo;

    request = malloc(sizeof (Request));

    request->count_mutex = malloc(sizeof (pthread_mutex_t));
    request->count_threshold_cv = malloc(sizeof (pthread_cond_t));

    pthread_cond_init(request->count_threshold_cv, NULL);
    pthread_mutex_init(request->count_mutex, NULL);

    pthread_mutex_lock(request->count_mutex);

    package = receivePackage(connection);
    strcpy(url, package->dados);
    tipo = package->tipo;
    maxClientDataSize = askMaxClientDataSize(connection);

    //finalize request
    switch (tipo) {
        case LS:
            //            request = createRequest(connection, LS);
            request->tipo = LS;
            setUrl(request, url);
            setMaxClientDataSize(request, maxClientDataSize);
            setStatus(request, READY);
            break;
        case WGET:
            //finalize request
            //            request = createRequest(connection, WGET);
            request->tipo = WGET;
            setUrl(request, url);
            setMaxClientDataSize(request, maxClientDataSize);
            setStatus(request, READY);
            break;
        case CLOSECONNECTION:
            pthread_exit(NULL);
            return;
            break;
        default:
            //            request = createRequest(connection, OTHER);
            request->tipo = OTHER;
            setStatus(request, READY);
            break;
    }
    addRequest(request);

    pthread_cond_wait(request->count_threshold_cv, request->count_mutex);

    pthread_mutex_unlock(request->count_mutex);
    pthread_cond_destroy(request->count_threshold_cv);
    pthread_mutex_destroy(request->count_mutex);

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

    request->count_mutex = malloc(sizeof (pthread_mutex_t));
    request->count_threshold_cv = malloc(sizeof (pthread_cond_t));
    pthread_cond_init(request->count_threshold_cv, NULL);
    pthread_mutex_init(request->count_mutex, NULL);
    pthread_mutex_lock(request->count_mutex);

    addRequest(request);

    pthread_cond_wait(request->count_threshold_cv, request->count_mutex);

    package = receivePackage(connection);

    pthread_mutex_unlock(request->count_mutex);
    pthread_cond_destroy(request->count_threshold_cv);
    pthread_mutex_destroy(request->count_mutex);

    return atoi(package->dados);
}