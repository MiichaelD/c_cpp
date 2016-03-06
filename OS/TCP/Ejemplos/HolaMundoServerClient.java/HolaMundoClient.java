/*
   Programa:  HolaMundoClient.java
   Autor:     Arnoldo Diaz Ramirez

*/

import java.io.*;
import java.net.*;

public class HolaMundoClient {
    public static void main(String[] args) throws IOException {

	Socket socket = null;
	PrintWriter out = null;
	BufferedReader in = null;

	if (args.length == 0) {
	    System.out.println("Debe ejecutarse asi: java HolaMundoClient host\n");
	    System.exit(1);
	} else
	    System.out.println("Solicitando conexion a " + args[0]);

	// se solicita conexion al host en el puerto 4444
        // y se crean los flujos de entrada y salida

	try {
	    socket = new Socket(args[0], 4444);
	    out = new PrintWriter(socket.getOutputStream(), true);
	    in = new BufferedReader(new InputStreamReader(
							  socket.getInputStream()));
	} catch (UnknownHostException e) {
	    System.err.println("HolaMundoClient: host " +  args[0] + " desconocido\n");
	    System.exit(1);
	} catch (IOException e) {
	    System.err.println("HolaMundoClient: no fue posible la conexion a "
			       + args[0]);
	    System.exit(1);
	}

    	String input;

	// se recibe informacion del servidor
	// y se imprime en pantallla

    	input = in.readLine();
	System.out.println("Recibido: " + input);
    	
	// se cierran flujos y conexion (socket)
    	out.close();
    	in.close();
   	socket.close();
    }
}
