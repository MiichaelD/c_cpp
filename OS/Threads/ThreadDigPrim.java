/*
 * 
 *    Programa:    	ThreadDigPrim.java (tarea 14)
 * 
 *    Objetivo:		Elaborar un programa en Lenguaje Java que lea dos número enteros A y B. 
 * 			El hilo main() deberá crear dos hilos.
 *			Un hilo aplicará el algoritmo digits utilizando los números, mientras
 * 			que el segundo hilo determinará cuántos números primos existen entre
 * 			A y B inclusive. El hilo main() imprimirá los resultados.
 * 
 *    Autor:        	Michael Duarte
 * 
 *    Fecha:		Noviembre 2012
 * 
 *    Nota:      	Compilar:  % javac *java
 *		  	Ejecutar:  % java ThreadDigPrim
 * 
 */

import java.lang.Thread;
import java.util.Scanner;
import java.util.Arrays;

class ThreadDigPrim{
  
  static int A,B,cont[],nPrimos;
  
  public static void main( String[] args ) {
    
   Scanner in=new Scanner(System.in);
   System.out.printf("Introduce 2 numeros: ");
   A=in.nextInt();
   B=in.nextInt();
   cont=new int[10];
    // se crea cada thread
    Thread digT = new Thread( new DigitsThread() );
    Thread priT = new Thread( new PrimosThread() );
    
    
    digT.start();
    priT.start();
    
    try{
      digT.join();
      priT.join();
    }catch(InterruptedException e){e.printStackTrace();}
    
    System.out.println("Digits:\t\t"+Arrays.toString(cont).replace(",","")+"\nNumeros Primos: "+nPrimos);
    
  } 
} 



class DigitsThread implements Runnable{
  
  public void run()
  {
    String string;
    for(int i=ThreadDigPrim.A;i<=ThreadDigPrim.B;i++){
      string=Integer.toString(i);
      for(int j=0;j<string.length();j++){//se recorren caracteres
	ThreadDigPrim.cont[(string.charAt(j)-'0')]++;}//se incrementa dependiendo de caracter que es
    }
  }
}

class PrimosThread implements Runnable{
  
  public void run(){
    ThreadDigPrim.nPrimos=0;
    for(int i=ThreadDigPrim.A;i<=ThreadDigPrim.B;i++){
      ThreadDigPrim.nPrimos+=esPrimo(i);
    }
  }
  
  byte esPrimo(int num){
    if( num <= 1 )
      return 0;// numeros primos deben ser mayores  a 1
      for(int j=num-1; j>1;j--)
	if(num%j == 0)
	  return 0;
    //System.out.printf("Numero primo: %d\n",num);
    return 1;
  }
}

