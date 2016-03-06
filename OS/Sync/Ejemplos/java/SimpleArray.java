// Programa: SimpleArray.java
// Clase que administra un arreglo de enteros que sera compartido por multiples 
// threads utilizando sincronizacion.
import java.util.Random;

public class SimpleArray
{
   private final int array[]; // arrego de enteros que sera compartido
   private int writeIndex = 0; // indice del siguiente elemento a escribir
   private final static Random generator = new Random();

   // construye un arreglo "SimpleArray" de tamaño "size"
   public SimpleArray( int size )
   {
      array = new int[ size ];
   } // fin del constructor

   // adiciona un valor al arreglo compartido
   public synchronized void add( int value )
   {
      int position = writeIndex; // se almacena el indice del elemento que se escribio

      try
      {
         // se pone a "dormir" al thread por for 0-499 milisegundos
         Thread.sleep( generator.nextInt( 500 ) ); 
      } // fin del try
      catch ( InterruptedException ex )
      {
         ex.printStackTrace();
      } // fin del catch

      // se coloca el valor en el elemento apropiado
      array[ position ] = value;
      System.out.printf( "%s escribio %2d al elemento %d.\n", 
         Thread.currentThread().getName(), value, position );

      ++writeIndex; // increment index of element to be written next
      System.out.printf( "Siguiente indice de escritura: %d\n", writeIndex );
   } // end method add
   
   // used for outputting the contents of the shared integer array
   public String toString()
   {
      String arrayString = "\nContenido del arreglo compartido:\n";
   
      for ( int i = 0; i < array.length; i++ )
         arrayString += array[ i ] + " ";
   
      return arrayString;
   } // end method toString
} // end class SimpleArray


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