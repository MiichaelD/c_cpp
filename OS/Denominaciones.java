/*
Programa:		Denominaciones.java
Objetivo:		Dado una cantidad de dinero, se debera imprimir el numero de 
			monedas/billetes de cada denominación existente.s

Autor:			Michael Duarte
Fecha:			Septiembre 2012

*/

public class Denominaciones{

	public static void main(String[] arg){
	Denominaciones b=new Denominaciones();
	int cantidad=183;
	if(arg.length==1){
		try{
		      cantidad=Integer.parseInt(arg[0]);
		}catch(Exception e){
			System.out.printf("Parametros deben ser numericos\n"); 
			System.exit(0);	
		}
	}
	System.out.printf("Cantidad: %d\n",cantidad);
	int[] denom=new int[]{50,20,10,5,2,1};
	int[] salida=b.diffDenom(cantidad,denom);
	b.salida(denom,salida);
	
	}
	
	public int[] diffDenom(int cantidad, int[] in){
		int temp;
		int[] exit=new int[in.length];
		for(int i=0;i<in.length&&cantidad>0;i++){
			if((temp=cantidad/in[i])>0){
				exit[i]=temp;
				cantidad-=temp*in[i];
			}
		}
		return exit;
		
	}
	
	public void salida(int[] denom,int[] res){
		for(int i=0;i<denom.length;i++){
			if(res[i]>0){
				System.out.printf("\t%d x $%d\n",res[i],denom[i]);
			}
		}
	}

}