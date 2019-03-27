import socket
import sys

MSG_TAMANHO_MAX = 100

# Leitura da porta a ser atribuida ao servidor
if len(sys.argv) < 3:
    print("python clienteUDP.py [ENDERECO SERVIDOR] [PORTA]")
porta      = int(sys.argv[1])
enderecoIP = sys.argv[2]
sporta     = int(sys.argv[3])

# Criacao do socket
csocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Identificacao local
endereco = ("", porta)
csocket.bind(endereco)


endServidor = (enderecoIP, sporta)

# Comunicacao
while True:
    msg = input("Msg: ").encode("ascii")
    nbytes = csocket.sendto(msg, endServidor)
    if nbytes != len(msg):
        print("Falhou ao enviar a mensagem")
        break

    msg, endServidor = csocket.recvfrom(MSG_TAMANHO_MAX)
    if not msg:
        print("Falhou para receber uma mensagem")
        break
    # print("Msg recebida: {}".format(msg)) # raw
    print("Msg recebida: {}".format(msg.decode("ascii")))
    
    if msg.decode("ascii") == "tchau":
        break

csocket.close()