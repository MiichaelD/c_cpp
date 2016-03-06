import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
if len(sys.argv) < 2:
    print('Ejecutar así: ClientTCP HostIP')
else:    
    #server_address = ('localhost', 4444)
    print('Parametro recibido: ',sys.argv[1])
    server_address = (sys.argv[1], 4444)
    #print >>sys.stderr, 'connecting to %s port %s' % server_address
    print ('connecting to %s port %s' % server_address, file=sys.stdout)
    sock.connect(server_address)
    
    try:
        
        # Send data
        message = input ('2 Numeros separados por espacio: ')
        print ('mensaje capturado: ',message)
        sock.sendall(bytes(message,"ascii"))
    
        # Look for the response
        data = sock.recv(1024)
        print(str(data))
    
    finally:
        sock.close()
