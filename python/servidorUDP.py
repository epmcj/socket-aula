import socket
import sys

MAX_CLIENTES    = 10
MSG_TAMANHO_MAX = 100

# Leitura da porta a ser atribuida ao servidor
if len(sys.argv) < 2:
    print("python servidorUDP.py [PORTA]")
porta = int(sys.argv[1])

# Criacao do socket
ssocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Identificacao local
endereco = ("", porta)
ssocket.bind(endereco)

# Comunicacao
while True:
    print("Esperando por novo cliente...")
    while True:
        msg, endCliente = ssocket.recvfrom(MSG_TAMANHO_MAX)
        if not msg:
            print("Falhou para receber uma mensagem")
            break
        print("Msg recebida: {}".format(msg.decode("utf-8")))
        
        nbytes = ssocket.sendto(msg, endCliente)
        if nbytes != len(msg):
            print("Falhou ao enviar a mensagem")
            break
        
        if msg.decode("utf-8") == "tchau":
            break

# Finalizacao
ssocket.close()
