#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/socket.h>

/**
 *  Esta estrutura é responsável por manter as informações sobre uma conexão.
 *  O principal objetivo é encapsular os detalhes relacionados à conexão 
 *  TCP/IP por IPv4 ou IPv6.
 */
typedef struct connection_t {
    int clientSock; //O socket conectado
    struct sockaddr* peerAddr; //Informações sobre o endereço do computador remoto
    socklen_t peerAddrLen; //Tamanho dos dados do endereço do computador remoto
    char* host; //Uma forma "imprimível" do endereço do computador remoto
    char* port; //Uma foma "imprimível" da porta conectada ao computador remoto.
} connection_t;

/**
 * Conecta ao computador host:port que está esperando para aceitar conexões externas.
 * @param host endereço IPv4 ou IPv6 do computador remoto
 * @param port porta do computador remoto a conectar
 * @return o endereço de uma nova connection_t ou NULL, caso hajam erros.
 */
connection_t* CONN_connectTo(char* host, char* port);

/**
 * Inicia a escuta em uma porta.
 * O retorno desta função deve ser usado na função CONN_accept para aceitar novas conexões.
 * @param port porta a ser escutada pelo processo
 * @return o socket da porta ou um erro fatal.
 */
int CONN_listenTo(char* port);

/**
 * Aceita uma conexão pendente no socket. Neste aceite, um novo socket é criado especificamente
 * para conectar ao novo host externo. listenSocket não é alterado e pode ser usado para aguardar mais
 * conexões. Caso não hajam conexões pendentes no socket, bloqueia até que uma nova conexão esteja disponível. 
 * @param listenSocket o socket usado para aguardar conexões. Deve ter sido aberto usando CONN_connectTo
 * @return o endereço de uma nova connection_t ou NULL, caso hajam erros.
 */
connection_t* CONN_accept(int listenSocket);

/**
 * 
 * @param connection a conexão a ser inspecionada
 * @return o socket correspondente à conexão.
 */
int CONN_getSocket(connection_t *connection);

/**
 * 
 * @param connection a conexão a ser inspecionada
 * @return uma string contendo a forma "imprimível" do endereço do computador remoto
 */
char* CONN_getPeerName(connection_t *connection);

/**
 * 
 * @param connection a conexão a ser inspecionada
 * @return uma string contendo a forma "imprimível" da porta conectada ao computador remoto
 */
char* CONN_getPeerPort(connection_t *connection);

/**
 * Envia dados para um computador remoto previamente conectado. Na realidade esta
 * função é um wrapper para a chamada de sistema send.
 * @param connection conexão ao computador remoto.
 * @param buffer buffer que contém os dados a serem enviados.
 * @param bufferLen quantidade de bytes no buffer a serem enviados
 * @param flags ver o campo flags da chamada de sistema send (man 2 send)
 * @see send
 * @return a quantidade de bytes enviados, -1 em caso de erro. Para ajudar, fiz com que
 * a função imprima na saída de erro padrão a mensagem correspondente ao erro. É importante
 * verificar o retorno dessa função para garantir que o dado foi enviado. Para mais detalhes,
 * veja a página do manual para send (man 2 send)
 */
int CONN_send(connection_t* connection, void* buffer, int bufferLen, int flags);

/**
 * Recebe dados de um computador remoto previamente conectado. Bloqueia se não há dados novos
 * a serem lidos. Na realidade esta função é um wrapper para a chamada de systema recv.
 * @param connection conexão ao computador remoto.
 * @param buffer buffer previamente alocado que guardará os dados recebidos.
 * @param bufferLen tamanho do buffer alocado.
 * @param flags ver o campo flags da chamada de sistema recv (man 2 recv)
 * @see recv
 * @return a quantidade de bytes recebidos ou -1 em caso de erro. Para ajudar, fiz com que
 * a função imprisa na saída de erro padrão a mensagem que corresponde ao erro. É
 * importante verificar o retorno dessa funç~ao para garantir que os dados foram recebidos.
 * Esta função retorna 0 caso o computador remoto desconecte, ou seja, é uma boa forma de verificar
 * se a conexão ainda está aberta. Para mais detalhes, veja a página do manual para recv (man 2 recv)
 */
int CONN_receive(connection_t* connection, void* buffer, int bufferLen, int flags);

/**
 * Fecha uma conexão e libera os recursos utilizados pela biblioteca.
 * @param connection conexão a ser liberada.
 */
void CONN_close(connection_t* connection);

#endif /* CONNECTION_H */

