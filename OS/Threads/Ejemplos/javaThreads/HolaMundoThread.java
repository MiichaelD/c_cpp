/*

    Programa:     HolaMundoThread.java

    Objetivo:     Mostrar el uso de Java Threads.

                  El programa crea 3 threads que envian un mensaje "Hola Mundo" y posteriormente
                  pasan a estado "timed waiting" por un tiempo aleatorio. Transcurrido ese tiempo
                  regresan a estado "Runnable" y concluyen su ejecucion.

                  El archivo HolaMundoThread.java contiene el codigo que sera ejecutado por cada thread

    Autor:        Arnoldo Diaz Ramirez (adaptado del ejemplo del libro "Java. How to Program, 7th Edition", Deitel and Deitel

    Nota:         Compilar:  % javac *java
		  Ejecutar:  % java HolaMundoThread_thc

*/



import java.util.Random;

public class HolaMundoThread implements Runnable
{
   private final int sleepTime; // tiempo aleatorio de espera (sleep) para cada thread
   private final String taskName; // nombre de la tareas
   private final static Random generator = new Random();

   public HolaMundoThread( String name )
   {
      taskName = name; // se especifica el nombre del thread
      System.out.printf( "Hola Mundo desde Java thread %s\n", taskName);
         // se obtiene un numero aleatorio de espera (pick) entre 0 y 5 segundos
      sleepTime = generator.nextInt( 5000 ); // millisegundos
   } // fin del constructor

         // metodo run que contiene el codigo que ejecutara el thread
   public void run()
   {
      try // se pone al thread en estado "timed waiting" (sleep) por el tiempo especificado en sleepTime
      {
         System.out.printf( "%s se va a dormir por %d milisegundod.\n",
         taskName, sleepTime );
         Thread.sleep( sleepTime ); // se "duerme" al thread
      } // fin try
      catch ( InterruptedException exception )
      {
         System.out.printf( "%s %s\n", taskName,
                            "terminado de manera prematura debido a alguna interrupcion" );
      } // fin catch

      System.out.printf( "%s despertando\n", taskName );

      } // fin del metodo run
   } // fin de la clase HolaMundoThread