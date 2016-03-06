/*
Programa:  		ServerTCP.java

Descripcion:		Implementar el modelo cliente-servidor utilizando sockets. El cliente, elaborado en Lenguaje C#,
                    solicitará dos números A y B al usuario, y enviará el valor de los números al servidor.
                El servidor, elaborado en Lenguaje Java, determinará cuantos números primos existen entre A y B, 
                    y aplicará el algortimo digits a los números A y B. Posteriormente, enviará los resultados al cliente.
                El cliente imprimirá los resultados en pantalla.
				
Autor:     		Michael Duarte

Fecha:			Octubre 2012

*/

import java.io.*;
import java.util.*;
import java.net.*;

public class ServerTCP {

	public static void main(String[] args) throws IOException {
		ServerSocket serverSocket = null;
		try {
			serverSocket = new ServerSocket(4444);
			//creamos serverSocket soporta hasta 1000 request en espera, bind puerto 4444, IP local
			//serverSocket = new ServerSocket(4444,1000,InetAddress.getLocalHost());
			System.out.println("Servidor establecido: "+serverSocket.toString());
		} catch (IOException e) {
			System.err.println("Error al conectarse al puerto: 4444.");
			System.exit(1);
		}
		
		try {//se crea un hilo para ejecutar cada cliente.
			while(true){
				new serverThread(serverSocket.accept());
				}
		} catch (IOException e) {
			System.err.println("Fallo en accept()");
			System.exit(1);
		}
		finally{//si hay error o no, cerrar server
			serverSocket.close();
		}
	}
}

class serverThread extends Thread{

	DataInputStream entrada;
	DataOutputStream salida;
	Socket socketCliente;
	
	public serverThread (Socket unSocketCliente) {
		try {
			socketCliente = unSocketCliente;
			System.out.println("Atendiendo a cliente: "+socketCliente.getInetAddress());
			entrada = new DataInputStream(socketCliente.getInputStream( ));
			salida = new DataOutputStream(socketCliente.getOutputStream( ));
			start();
		} catch(IOException e){
			System.out.println("serverThread:"+e.getMessage());
		}
	}
	public void run( ){
		try {	  
			int num1,num2,digits[],nPrimos=0,numBytes;
			byte arr[]=new byte[1024];
			String msj;
			
			
			numBytes=entrada.read(arr);
			msj=new String(arr,0,numBytes);
			System.out.println("mensaje recibido: "+msj);
			num1=Integer.parseInt(msj.split("\\s")[0]);
			num2=Integer.parseInt(msj.split("\\s")[1]);
			
			
			
			digits=new int[10];
			
			Digits(digits,num1,num2);
			
			for (int i=num1;i<=num2;i++){
				nPrimos+=esPrimo(i);
			}
			
			msj="Digits: \t"+Arrays.toString(digits).replace(", "," ")+"\nNumeros Primos: "+nPrimos;
			arr=msj.getBytes();
			salida.write(arr,0,arr.length);
		
		
			entrada.close();
			salida.close();
			socketCliente.close();
			System.out.println("Terminamos de atender a cliente: "+socketCliente.getInetAddress());
		} catch(EOFException e) {System.out.println("EOF: "+e.getMessage( )); System.exit(1);
		} catch(IOException e) {System.out.println("IO: "+e.getMessage( )); System.exit(1);}
		
	}
	
	byte esPrimo(int num){
		if( num <= 1 )
			return 0;// numeros primos deben ser mayores  a 1
		for(int j=num-1; j>1;j--)
			if(num%j == 0)
				return 0;
		//printf("Numero primo: %d\n",num);
		return 1;
	}
	
	void Digits(int cont[],int n1, int n2){
	int i,j;
	String string;
		for(i=n1;i<=n2;i++){
			string=Integer.toString(i);
            for(j=0;j<string.length();j++){//se recorren caracteres
				cont[(string.charAt(j)-'0')]++;}//se incrementa dependiendo de caracter que es
            }
	}
	
	
}