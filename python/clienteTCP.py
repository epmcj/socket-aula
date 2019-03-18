import socket
import sys

MSG_TAMANHO_MAX = 100

# Leitura da porta a ser atribuida ao servidor
if len(sys.argv) < 3:
    print("python clienteTCP.py [ENDERECO] [PORTA]")
enderecoIP = sys.argv[1]
porta      = int(sys.argv[2])

# Criacao do socket
csocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conexao (abertura ativa)
endServidor = (enderecoIP, porta)

csocket.connect(endServidor)

# Comunicacao
while True:
    msg = input("Msg: ").encode()
    nbytes = csocket.send(msg)
    if nbytes != len(msg):
        print("Falhou ao enviar a mensagem")
        break

    msg = csocket.recv(MSG_TAMANHO_MAX)
    if not msg:
        print("Falhou para receber uma mensagem")
        break
    print("Msg recebida: {}".format(msg.decode("utf-8")))
    
    if msg.decode("utf-8") == "tchau":
        break

csocket.close()