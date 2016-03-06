/*
   Programa:  HolaMundoServer.java
   Autor:     Arnoldo Diaz Ramirez

*/

import java.io.*;
import java.net.*;

public class HolaMundoServer {

    public static void main(String[] args) throws IOException {

	// se crea en socket del servidor
        // para recibir conexiones

        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(4444);
        } catch (IOException e) {
            System.err.println("Error al conectarse al puerto: 4444.");
            System.exit(1);
        }

	// se espera por alguna conexion
	// de algun cliente

        Socket clientSocket = null;
        try {
            clientSocket = serverSocket.accept();
        } catch (IOException e) {
            System.err.println("Fallo en accept()");
            System.exit(1);
        }


	// se cran los flujos de entrada y salida
	// para comunicarse con el cliente

        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        BufferedReader in = new BufferedReader(
				new InputStreamReader(
				clientSocket.getInputStream()));

        String hola = "Hola a todos desde un servidor Java!";

	// se envia un mensaje al cliente
        out.println(hola);

	// se cierran flujos y socket

        out.close();
        in.close();
        clientSocket.close();
        serverSocket.close();
    }
}
