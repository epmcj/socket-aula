all: cli-serTCP cli-serUDP

cli-serTCP: clienteTCP servidorTCP

cli-serUDP: clienteUDP servidorUDP

clienteTCP: cliente_tcp.c
	gcc -o clienteTCP cliente_tcp.c

servidorTCP: servidor_tcp.c
	gcc -o servidorTCP servidor_tcp.c

clienteUDP: cliente_udp.c
	gcc -o clienteUDP cliente_udp.c

servidorUDP: servidor_udp.c
	gcc -o servidorUDP servidor_udp.c

clear:
	rm clienteTCP clienteUDP servidorTCP servidorUDP