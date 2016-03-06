/*
Programa:  		ClientTCP.java

Descripcion:		Implementar el modelo cliente-servidor utilizando sockets, en Lenguaje Java.
					El cliente solicitará dos números A y B al usuario, y enviará el valor de los números al servidor.
					El servidor determinará cuantos números primos existen entre A y B, y aplicará el algortimo
					digits a los números A y B. Posteriormente, enviará los resultados al cliente.
					El cliente imprimirá los resultados en pantalla
					
Autor:     		Michael Duarte

Fecha:			Octubre 2012

*/
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ClientTCP {
	public static void main(String[] args) throws IOException {

		Socket socket = null;
		DataOutputStream out = null;
		DataInputStream in = null;
		int num1,num2,numBytes;
		

		if (args.length == 0) {
			System.out.println("Debe ejecutarse asi: java ClientTCP IP del Host\n");
			System.exit(1);
		}
		System.out.println("Solicitando conexion a " + args[0]);

		try {
			socket = new Socket(args[0], 4444);
			out = new DataOutputStream(socket.getOutputStream());
			in = new DataInputStream(socket.getInputStream());
			byte[] arr;

			Scanner input=new Scanner(System.in);
			arr=input.nextLine().getBytes();
			out.write(arr,0,arr.length);
			
			arr=new byte[1024];//inicializamos nuevo buffer con espacio suficiente
			
			numBytes=in.read(arr);//recibimos
			System.out.println(new String(arr,0,numBytes));
			
		} catch (UnknownHostException e) {
			System.err.println("Client: host "+args[0]+" desconocido\n");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("Client: no fue posible la conexion a "+args[0]);
			System.exit(1);
		} finally {
			out.close();
			in.close();
			socket.close();
		}
	}
}
