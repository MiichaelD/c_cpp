/*
Programa:  		ClientTCP.cs

Descripcion:		Implementar el modelo cliente-servidor utilizando sockets. El cliente, elaborado en Lenguaje C#,
                    solicitará dos números A y B al usuario, y enviará el valor de los números al servidor.
                El servidor, elaborado en Lenguaje Java, determinará cuantos números primos existen entre A y B, 
                    y aplicará el algortimo digits a los números A y B. Posteriormente, enviará los resultados al cliente.
                El cliente imprimirá los resultados en pantalla.
					
Autor:     		Michael Duarte

Fecha:			Octubre 2012

*/


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace ClientTCP
{

    public class ClientTCP
    {//SynchronousSocketClient {

        public static void StartClient(String IpHost) {
            if(IpHost.Equals("localhost"))
                IpHost=Dns.GetHostName();


        // Data buffer for incoming data.
        byte[] bytes = new byte[1024];

        // Connect to a remote device.
        try {
            // Establish the remote endpoint for the socket.
            // This example uses port 4444 on the local computer.
            IPHostEntry ipHostInfo = Dns.Resolve(IpHost);
            IPAddress ipAddress = ipHostInfo.AddressList[0];
            IPEndPoint remoteEP = new IPEndPoint(ipAddress,4444);

            // Create a TCP/IP  socket.
            Socket sender = new Socket(AddressFamily.InterNetwork, 
                SocketType.Stream, ProtocolType.Tcp );

            // Connect the socket to the remote endpoint. Catch any errors.
            try {
                sender.Connect(remoteEP);

                Console.WriteLine("Socket connected to {0} successfully\n", sender.RemoteEndPoint.ToString());

                // Encode the data string into a byte array.


                Console.Write("Introduce 2 numeros separados por un espacio: ");

                String msj=Console.ReadLine();

                byte[] msg = Encoding.ASCII.GetBytes(msj);

                // Send the data through the socket.
                int bytesSent = sender.Send(msg);

                // Recibimos Digits y primos.
                int bytesRec = sender.Receive(bytes);
                Console.WriteLine("{0}",  Encoding.ASCII.GetString(bytes,0,bytesRec));

               // Release the socket.
                sender.Shutdown(SocketShutdown.Both);
                sender.Close();
                
            } catch (ArgumentNullException ane) {
                Console.WriteLine("ArgumentNullException : {0}",ane.ToString());
            } catch (SocketException se) {
                Console.WriteLine("SocketException : {0}",se.ToString());
            } catch (Exception e) {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }

        } catch (Exception e) {
            Console.WriteLine( e.ToString());
        }
    }

        public static int Main(String[] args)
        {
            if (args.Length == 0) {
                Console.WriteLine("Ejecturar el programa asi: ClientTCP IpHost");
                return 0;
            }
            StartClient(args[0]);;
            return 0;
        }
    }
}
