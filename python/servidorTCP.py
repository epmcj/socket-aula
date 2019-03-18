import socket
import sys

MAX_CLIENTES    = 10
MSG_TAMANHO_MAX = 100

# Leitura da porta a ser atribuida ao servidor
if len(sys.argv) < 2:
    print("python servidorTCP.py [PORTA]")
porta = int(sys.argv[1])

# Criacao do socket
ssocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Abertura passiva
endereco = ("", porta)
ssocket.bind(endereco)
ssocket.listen(MAX_CLIENTES)

while True:
    print("Esperando por novo cliente...")

    csocket, cliente = ssocket.accept()
    print("Conectado a {}".format(cliente))
    
    # Comunicacao
    while True:
        msg = csocket.recv(MSG_TAMANHO_MAX)
        if not msg:
            print("Falhou para receber uma mensagem")
            break
        print("Msg recebida: {}".format(msg.decode("utf-8")))
        
        nbytes = csocket.send(msg)
        if nbytes != len(msg):
            print("Falhou ao enviar a mensagem")
            break
        
        if msg.decode("utf-8") == "tchau":
            break
    # Finalizacao
    csocket.close()

ssocket.close()
