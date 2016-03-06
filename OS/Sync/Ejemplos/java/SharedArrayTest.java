// Programa: SharedArrayTest.java
// Ejecuta dos threads (Runnables) que adicionan elementos al arreglo compartido sharedSimpleArray.
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

public class SharedArrayTest
{
   public static void main( String[] arg )
   {
      // se construye el objeto compartido sharedSimpleArray
      SimpleArray sharedSimpleArray = new SimpleArray( 6 );

      // se crean dos tareas (threads) que escribiran en el arreglo compartido
      ArrayWriter writer1 = new ArrayWriter( 1, sharedSimpleArray );
      ArrayWriter writer2 = new ArrayWriter( 11, sharedSimpleArray );

      // se ejecutan las tareas con un ExecutorService
      ExecutorService executor = Executors.newCachedThreadPool();
      executor.execute( writer1 );
      executor.execute( writer2 );

      executor.shutdown();

      try
      {
         // se espera por un minuto a que ambas tareas concluyan su ejecucion
         boolean tasksEnded = executor.awaitTermination( 
            1, TimeUnit.MINUTES );

         if ( tasksEnded )
            System.out.println( sharedSimpleArray ); // se imprime el contenido
         else
            System.out.println( 
               "Tiempo expirado al esperar que concluyera la tarea." );
      } // fin del try
      catch ( InterruptedException ex )
      {
         System.out.println( 
            "Interrumpido mientras esperana a que las tareas concluyeran." );
      } // fin del catch
   } // fin del main
} // fin de la clase SharedArrayTest


/**************************************************************************
 * (C) Copyright 1992-2007 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/