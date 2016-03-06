/*
Programa:  		ThreadDigPrim.cs (tarea 15)

Descripcion:	Hilo main pedira 2 numeros y creara 2 hilos, uno aplicara el 
				algoritmo Digits y otro contara numeros primos.
				Hilo main deberá imprimir los resultados.
					
Autor:     		Michael Duarte

Fecha:			Noviembre 2012

Nota:			Compilado usando Mono - Ubuntu
				Tutorial Hilos C#: http://msdn.microsoft.com/en-us/library/aa645740(v=vs.71).aspx
		
				Compilar:	gmcs ThreadDigPrims.cs
				Ejecutar:	mono ThreadDigPrims.exe o ./ThreadDigPrims.exe

*/
using System;
using System.Threading;
using System.Text;

namespace ThreadDigPrims{

    public class ThreadsMain
    {
        public static int Main(String[] args)
        {
        	Console.Write("Introduce primer numero:");
			A=int.Parse(Console.ReadLine());
			Console.Write("Introduce segundo numero:");
			B=int.Parse(Console.ReadLine());
			
			Hilos oHilos=new Hilos();
			
			Thread digT=new Thread(new ThreadStart(oHilos.Digits));
			Thread primT=new Thread(new ThreadStart(oHilos.Primos));
			
			digT.Start();
			primT.Start();
			
			digT.Join();
			Console.Write("Digits: \t");
			for(int i=0;i<10;i++)
				Console.Write(cont[i]+" ");
			Console.WriteLine();
			
			primT.Join();
			Console.WriteLine("Numeros Primos: "+nPrimos);
			
			
            return 0;
        }
		
		public static int A,B,nPrimos;
		public static int[] cont;
    }
	
	
	public class Hilos
	{
		public void Digits()
		{
			string strin;
			ThreadsMain.cont=new int[10];
    		for(int i=ThreadsMain.A;i<=ThreadsMain.B;i++){
      			strin=i.ToString();
      			for(int j=0;j<strin.Length;j++){//se recorren caracteres
					ThreadsMain.cont[(strin[j]-'0')]++;}//se incrementa dependiendo de caracter que es
    		}
		}
		
		
		public void Primos()
		{
			ThreadsMain.nPrimos=0;
    		for(int i=ThreadsMain.A;i<=ThreadsMain.B;i++){
      			ThreadsMain.nPrimos+=esPrimo(i);
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
}
