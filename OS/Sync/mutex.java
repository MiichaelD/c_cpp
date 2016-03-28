/*
Programa:    mutex.java

Objetivo:    Elaborar un programa que cree un hilo. Los dos hilos, esto es, el hilo "main" y el hilo creado,
		actualizarán la variable global "cont" que tendrá un valor inicial igual a cinco.

		El hilo "main" ejecutará el siguiente código, después de crear al otro hilo:
			(3 veces){
			for (i=1; i<1000; i++)
			for (j=1; j<1000; j++);
			cont++;
			}
		
		El otro hilo ejecutará el mismo código, con la diferencia de que decrementará en uno el valor
		del contador (cont--) en lugar de incrementarlo (cont++). Esto es, el hilo "main" incrementará
		tres veces en uno el valor de cont, mientras que el otro hilo lo decrementará tres veces.
		
		Como puedes observar, el uso de la variable cont es una sección crítica. Para evitar
		inconsistencia en el resultado final, deberás utilizar el API para Mutex de java o C# (por ejemplo,
		pthread_mutex_lock()) para el acceso a la sección crítica.

		Finalmente, el hilo "main" esperará a que el otro hilo concluya su ejecución (esto es, haga un
		pthread_join() o su equivalente en Java o C#) e imprimirá el valor final de la variable cont.
	


	Autor:    	Michael Duarte
	
	Fecha: 		Diciembre 2012
*/ 



class Main{

	int cont=5;
	
	public static void main(String[] args) throws InterruptedException {
		final Main m=new Main();

		Thread h1=new Thread(new Runnable(){
			public void run(){
				m.funcionHilo();
			}
		});
		
		h1.start();

		int hi,j;
		for(h = 0; h < 3; ++h){
		 	for (i=0; i<1000; ++i)
				for (j=0; j<1000; ++j);
			m.crementar(1);
		}
		h1.join();
		System.out.println("Contador Inicial: 5\nContador Final:   "+m.cont);
	}
	
	void funcionHilo() {
		int h,i,j;
		for(h = 0; h < 3; ++h){
		 	for (i=1; i<1000; i++)
				for (j=1; j<1000; j++);
			m.crementar(-1);
		}
	}

	public synchronized void crementar(int x){
		if(x<0)//decrementamos
			--cont;
		else//incrementamos
			++cont;
	}

}
