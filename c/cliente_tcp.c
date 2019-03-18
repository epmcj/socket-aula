#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MSG_TAMANHO_MAX 100

int main(int argc, char const *argv[]) {
    int csocket, porta, nbytes, err;
    char *enderecoIP, msg[MSG_TAMANHO_MAX];
    struct sockaddr_in endServidor;

    /* Leitura dos dados do servidor */
    if (argc < 3) {
        printf("./clienteTCP [ENDERECO] [PORTA]\n");
        exit(1);
    }
    enderecoIP = argv[1];
    porta      = atoi(argv[2]);

    /* Criacao do socket */
    csocket = socket(AF_INET, SOCK_STREAM, 0);
    if (csocket < 0) {
        printf("Falhou ao criar o socket.\n");
        exit(1);
    }


    /* Conexao (abertura ativa) */
    memset(&endServidor, 0, sizeof(endServidor));
    endServidor.sin_family      = AF_INET;
    endServidor.sin_addr.s_addr = inet_addr(enderecoIP);
    endServidor.sin_port        = htons(porta);
    
    err = connect(csocket, (struct sockaddr*) &endServidor, sizeof(endServidor));
    if (err < 0) {
        printf("Falhou ao se conectar ao servdor.\n");
        exit(1);
    }
    
    /* Comunicacao */
    do {
        printf("Msg: ");
        scanf("%s", msg);
        nbytes = send(csocket, msg, strlen(msg)+1, 0);
        if (nbytes < 0) {
            printf("Falhou ao enviar a mensagem.\n");
            break;
        }

        nbytes = recv(csocket, msg, MSG_TAMANHO_MAX, 0);
        if (nbytes < 0) {
            printf("Falhou ao receber uma mensagem.\n");
            break;
        }
        printf("Msg recebida: %s\n", msg);

    } while(strcmp(msg, "tchau"));
    
    /* Fechamento */
    close(csocket);

    return 0;
}
