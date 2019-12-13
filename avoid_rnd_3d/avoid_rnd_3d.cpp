//Programa que realiza el self avoiding walk en 3d

#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>

// double desplazamiento();
 
int main()
{
  //Se crean variables que  dan la cantidad de caminos que se realzan (N) y la cantidad de pasos por camino (Steps)
  int N=10000;//Repeticiones
  int Steps=100;

  int pasos=Steps;//Variable utilizada para  parar el programa si el camino aleatorio se encuentra con un punto sin salida posible.
  int dim=3;//Dimension del programa
  int contador=0;//Cuenta los pasos que se van realizando
  int max_vec=dim*2; //Cantidad maxima de vecinos que puede tener cada punto
  double random=0.0;
  int x1=0,x2=0,x3=0;//Variables temporales donde guardo los cambios de las respectivas coordenads

  // int part[max_vec];//sectores que se divide la unidad
  //int X1[Steps*N];
  //  int X2[Steps*N];
  //  int X3[Steps*N];
  //  int Avg[Steps]; //Valor promedio de la posicion

  int *part= new int[max_vec];//sectores que se divide la unidad
  int *X1= new int[Steps*N];
  int *X2= new int[Steps*N];
  int *X3= new int[Steps*N];
  int *Avg= new int[Steps]; //Valor promedio de la posicion
  
  ///////////////////////////////////////////////////////////////////////////////////////
  //Inicializo los arreglos que se van a utilizar
  
  for(int i=1;i<=max_vec;++i)
    part[i-1]=i*1.0;
  
   for(int i=0;i<Steps*N;++i)
     {
       X1[i]=0;  X2[i]=0; X3[i]=0;
     }

   for(int i=0;i<Steps;++i)
     Avg[i]=0;
     
   //////////////////////////////////////////////////////////////////////////////////////
   //Algoritmo que permite generar numeros aleatorios
   
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
   // int seed=1;
   //  std::mt19937 gen(seed);
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_real_distribution<> dis(0.0,  1.0);

   //////////////////////////////////////////////////////////////////////////////////////
   // Inicio funcion que calcula el camino aleatorio en tres dimensions
   
   for(int i=0;i<N;++i)// bucle que realiza diferentes caminos
     {
       for(int j=0;j<Steps-1;++j)// Bucle que da cada paso aleatorio
	 {
	   for(int i=1;i<=max_vec;++i)
	     part[i-1]=i*1.0;
	    
	   random=dis(gen); // Se genera numero aleatorio
	   
	   ///////////////////////////////////////////////////////////////////
	   // Algoritmo que verifica puntos recorridos

	   for(int k=0;k<j;k++)
	     {
	       if(X2[j+i*Steps]==X2[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps])//Reviso si la posicion j-esima de X2 ya esta ocupada en otra posicion k-esima
		 {
		   if(X1[j+i*Steps]+1==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps]) //Reviso si la posicion siguiente a X1 de j corresponde a la poscion k-esima de X1 (con esto comparo las parejas (X1[j]+1,X2[j]) y la posicion ya ocupada (X1[k],X2[k]) )
		     {
		       part[0]=0.0;
		       max_vec--;
		     }
		   if(X1[j+i*Steps]-1==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps])
		     {
		       part[1]=0.0;
		       max_vec--;
		     }
		 }

	       if(X1[j+i*Steps]==X1[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps])
		 {
		   if(X2[j+i*Steps]+1==X2[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps])
		     {
		       part[2]=0.0;
		       max_vec--;
		     }
		   if(X2[j+i*Steps]-1==X2[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps])
		     {
		       part[3]=0.0;
		       max_vec--;
		     }
		 }
	       
	       if(X1[j+i*Steps]==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps])
		 {
		   if(X3[j+i*Steps]+1==X3[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps])
		     {
		       part[4]=0.0;
		       max_vec--;
		     }
		   if(X3[j+i*Steps]-1==X3[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps])
		     {
		       part[5]=0.0;
		       max_vec--;
		     }
		 }
	     }

	   if(max_vec<1){
	     if(j+1<pasos)
	       {
	     pasos=j+1;

	       }//j=Steps;
	     max_vec=dim*2;
	     break;
	   }
	   
	 //exit(-1);}//no hay mas espacios hacia donde moverse por lo tanto debo terminar el programa
       double kk=0;
       for(int k=0;k<dim*2;k++)
	 {
	   if(part[k]>0.0){
	     kk+=1; part[k]=kk;
	   }
	 }




	   ////////////////////////////////////////////////////////////////
 
	   if(random<part[0]*1.0/max_vec){//Algoritmo que desice entre las posibilidades a moverse en funcion del numero random
	     x1+=1;
	   }
	   else if(random<part[1]*1.0/max_vec ){
	     x1-=1;
	   }
	   else if(random<part[2]*1.0/max_vec){
	     x2+=1;
	   }
	   else if(random<part[3]*1.0/max_vec){
	     x2-=1;
	   }
	   else if(random<part[4]*1.0/max_vec){
	     x3+=1;
	   }
	   else if(random<part[5]*1.0/max_vec){
	     x3-=1;
	   }
	   //Actualizo las posiciones y las guardo en dos arreglos 

	   X1[j+1+i*Steps]=x1+X1[j+i*Steps];
	   X2[j+1+i*Steps]=x2+X2[j+i*Steps];
	   X3[j+1+i*Steps]=x3+X3[j+i*Steps];
	   x1=0;
	   x2=0;
	   x3=0;
	   max_vec=dim*2;
	 }
     }

   //Se imprime cada punto del camino realzado y su respectivo calor r^2
   
   for(int i=0;i<pasos;++i)
     {
       for(int j=i;j<Steps*N;j+=Steps)
	 {
	   // printf(" %4d %4d %4d ",X1[j],X2[j],X3[j]);
	   Avg[i]+=X1[j]*X1[j]+X2[j]*X2[j]+X3[j]*X3[j];
	 }
       printf(" %5d %7.3f ",contador,Avg[i]*1.0/N);
       contador++;

       for(int j=i;j<Steps*N;j+=Steps)
	 printf(" %4d %4d %4d ",X1[j],X2[j],X3[j]);

       printf("\n");
	 
     }

   delete [] part;//sectores que se divide la unidad
   delete [] X1;
   delete [] X2;
   delete [] X3;
   delete [] Avg; //Valor promedio de la posicion
 
   
 return 0;
}

