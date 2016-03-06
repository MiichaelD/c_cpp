import socket
import sys

def primos(num):
    if i < 2:
        return 0# numeros primos deben ser mayores  a 1
    j = i
    while j > 2:
         j = j-1
         #print('Recorrido: %d / %d res = %d',i,j,i%j)
         if (i%j) == 0:
             return 0
    #print('numero primo: %d' % i)
    return 1

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 4444)#localhost answers to 127.0.0.1
print('starting up on %s port %s' % server_address)
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        print('connection from', client_address)

        # Receive the data in small chunks and retransmit it
        data = connection.recv(1024)
        print('received "%s"' % str(data))
        
        num1 = int(float(data.split()[0]))
        num2 = int(float(data.split()[1]))
		
        nPrimos = 0 
		
        for i in range(num1,num2+1):#primos!
             nPrimos+=primos(i)

        cont = [0,0,0,0,0,0,0,0,0,0]#Digits!
        for i in range(num1,num2+1):
             for j in range(0,len(str(i))):
                 cont[int(str(i)[j])]+=1
                 
        data='Digits: '+str(cont)+'          \nNumeros primos: %d'%nPrimos
        connection.sendall(bytes(data,"ascii"))
        
            
    finally:
        # Clean up the connection
        connection.close()
