#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MSG_TAMANHO_MAX 100

int main(int argc, char const *argv[]) {
    int csocket, porta, sporta, nbytes, err;
    char *enderecoIP, msg[MSG_TAMANHO_MAX];
    struct sockaddr_in endereco, endServidor;
    int tamEndereco = sizeof(endServidor);

    /* Leitura dos dados do servidor */
    if (argc < 4) {
        printf("./clienteUDP [PORTA] [ENDERECO SERVIDOR] [PORTA SERVIDOR]\n");
        exit(1);
    }
    porta      = atoi(argv[1]);
    enderecoIP = argv[2];
    sporta     = atoi(argv[3]);

    /* Criacao do socket */
    csocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (csocket < 0) {
        printf("Falhou ao criar o socket.\n");
        exit(1);
    }

    /* Identificacao local */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family      = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port        = htons(porta);

    err = bind(csocket, (struct sockaddr*) &endereco, sizeof(endereco));
    if (err < 0) {
        printf("Falhou ao associar endereco.\n");
        exit(1);
    }

    /* Endereco do servidor */
    memset(&endServidor, 0, sizeof(endServidor));
    endServidor.sin_family      = AF_INET;
    endServidor.sin_addr.s_addr = inet_addr(enderecoIP);
    endServidor.sin_port        = htons(sporta);
    
    /* Comunicacao */
    do {
        printf("Msg: ");
        scanf("%s", msg);
        nbytes = sendto(csocket, msg, strlen(msg)+1, 0, 
                        (struct sockaddr*) &endServidor, sizeof(endServidor));
        if (nbytes < 0) {
            printf("Falhou ao enviar a mensagem.\n");
            break;
        }

        nbytes = recvfrom(csocket, msg, MSG_TAMANHO_MAX, 0, 
                          (struct sockaddr*) &endServidor, &tamEndereco);
        if (nbytes < 0) {
            printf("Falhou ao receber uma mensagem.\n");
            break;
        }
        printf("Msg recebida: %s\n", msg);

    } while(strcmp(msg, "tchau"));
    
    return 0;
}
