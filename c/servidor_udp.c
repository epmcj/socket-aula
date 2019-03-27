#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MSG_TAMANHO_MAX 100
#define MAX_CLIENTES    10

int main(int argc, char const *argv[]) {
    int ssocket, porta, nbytes, err;
    char msg[MSG_TAMANHO_MAX];
    struct sockaddr_in endereco, endCliente;
    int tamEndereco = sizeof(endCliente);

    /* Leitura da porta a ser atribuida ao servidor */
    if (argc < 2) {
        printf("./servidorUDP [PORTA]\n");
        exit(1);
    }
    porta = atoi(argv[1]);

    /* Criacao do socket */
    ssocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (ssocket < 0) {
        printf("Falhou ao criar o socket.\n");
        exit(1);
    }

    /* Identificao local */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family      = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port        = htons(porta);

    err = bind(ssocket, (struct sockaddr*) &endereco, sizeof(endereco));
    if (err < 0) {
        printf("Falhou ao associar endereco.\n");
        exit(1);
    }

    while(1) {
        printf("Esperando por nova mensagem...\n");

        /* Comunicacao */
        nbytes = recvfrom(ssocket, msg, MSG_TAMANHO_MAX, 0, 
                            (struct sockaddr*) &endCliente, &tamEndereco);
        if (nbytes < 0) {
            printf("Falhou ao receber uma mensagem.\n");
            break;
        }
        msg[nbytes] = 0;
        printf("Msg recebida: %s\n", msg);

        nbytes = sendto(ssocket, msg, nbytes, 0, 
                        (struct sockaddr*) &endCliente, sizeof(endCliente));
        if (nbytes < 0) {
            printf("Falhou ao enviar a mensagem.\n");
            break;
        }
    }

    close(ssocket);

    return 0;
}
