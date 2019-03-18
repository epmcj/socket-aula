#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MSG_TAMANHO_MAX 100
#define MAX_CLIENTES    10

int main(int argc, char const *argv[]) {
    int ssocket, csocket, porta, nbytes, err;
    char msg[MSG_TAMANHO_MAX];
    struct sockaddr_in endereco, endCliente;
    int tamEndereco = sizeof(endCliente);

    /* Leitura da porta a ser atribuida ao servidor */
    if (argc < 2) {
        printf("./servidorTCP [PORTA]\n");
        exit(1);
    }
    porta = atoi(argv[1]);

    /* Criacao do socket */
    ssocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ssocket < 0) {
        printf("Falhou ao criar o socket.\n");
        exit(1);
    }

    /* Abertura passiva */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family      = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port        = htons(porta);

    err = bind(ssocket, (struct sockaddr*) &endereco, sizeof(endereco));
    if (err < 0) {
        printf("Falhou ao associar endereco.\n");
        exit(1);
    }

    err = listen(ssocket, MAX_CLIENTES);
    if (err < 0) {
        printf("Falhou ao marcar o socket para escutar.\n");
        exit(1);
    }

    while(1) {
        printf("Esperando por novo cliente...\n");

        csocket = accept(ssocket, (struct sockaddr*) &endCliente, &tamEndereco);
        if (csocket < 0) {
            printf("Falhou ao se conectar a um cliente.\n");
            exit(1);
        }

        printf("Conectado a %s\n", inet_ntoa(endCliente.sin_addr));

        /* Comunicacao */
        do {
            nbytes = recv(csocket, msg, MSG_TAMANHO_MAX, 0);
            if (nbytes < 0) {
                printf("Falhou ao receber uma mensagem.\n");
                break;
            }
            printf("Msg recebida: %s\n", msg);

            nbytes = send(csocket, msg, strlen(msg) + 1, 0);
            if (nbytes < 0) {
                printf("Falhou ao enviar a mensagem.\n");
                break;
            }

        } while(strcmp(msg, "tchau"));

        /* Finalizacao */
        close(csocket);
    }

    close(ssocket);

    return 0;
}
