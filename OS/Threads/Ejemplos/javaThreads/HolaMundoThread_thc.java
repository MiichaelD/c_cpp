/*

    Programa:     HolaMundoThread.java

    Objetivo:     Mostrar el uso de Java Threads.

                  El programa crea 3 threads que envian un mensaje "Hola Mundo" y posteriormente
                  pasan a estado "timed waiting" por un tiempo aleatorio. Transcurrido ese tiempo
                  regresan a estado "Runnable" y concluyen su ejecucion.

                  El programa HolaMundoThread.java crea e inicia tres hilos "HolaMundoThread" y ejecuta "Runnables"

    Autor:        Arnoldo Diaz Ramirez (adaptado del ejemplo del libro "Java. How to Program, 7th Edition", Deitel and Deitel

    Nota:         Compilar:  % javac *java
		  Ejecutar:  % java HolaMundoThread_thc

*/

import java.lang.Thread;

public class HolaMundoThread_thc
{
   public static void main( String[] args )
   {
      System.out.println( "Creando los threads" );

          // se crea cada thread
      Thread thread1 = new Thread( new HolaMundoThread( "task1" ) );
      Thread thread2 = new Thread( new HolaMundoThread( "task2" ) );
      Thread thread3 = new Thread( new HolaMundoThread( "task3" ) );

      System.out.println( "Threads creados, se inciian las tareasd (tasks)." );

            // se inician los threads y se ponen en estado "runnable"

      thread1.start(); // se invoca al metodo "run" de task1
      thread2.start(); // se invoca al metodo "run" de task2
      thread3.start(); // se invoca al metodo "run" de task3

      System.out.println( "Tareas iniciadas, termina main.\n" );

    } // fin main
 } // fin de la clase HolaMundoThread_thc (thread creator)
