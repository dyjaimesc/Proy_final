//Programa que realiza el camino aleatorio en 2d

#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>

// double desplazamiento();
 
int main()
{
  //creo variables que me dan la cantidad de caminos que realzo (N) y la cantidad de pasos por camino (Steps)
  int N=5000;//Repeticiones
  int Steps=1000;

  int pasos=Steps;//Variable utilizada para  parar el programa si el camino aleatorio se encuentra con un punto sin salida posible.
  int dim=2;//Dimension del programa
  int contador=0;//Cuenta los pasos que se van realizando
  int max_vec=dim*2; //Cantidad maxima de vecinos que puede tener cada punto
  double random=0.0;
  int x1=0,x2=0;//Variables temporales donde guardo los cambios de las respectivas coordenads

  // int part[max_vec];//sectores que se divide la unidad
  // int X1[Steps*N];
  // int X2[Steps*N];
  //int Avg[Steps]; //Valor promedio de la posicion

  int *part= new int[max_vec];//sectores que se divide la unidad
  int *X1= new int[Steps*N];
  int *X2= new int[Steps*N];
  int *Avg= new int[Steps]; //Valor promedio de la posicion
  
   
  // int *X= new int[N+1];
  // int *Y= new int[N+1];
  // int *Avg= new int[Steps+1]; //Valor promedio de la posicion
  // for(int i=0;i<=Steps;++i)
 

  ///////////////////////////////////////////////////////////////////////////////////////
  //Inicializo los arreglos que se van a utilizar
  
  for(int i=1;i<=max_vec;++i)
    part[i-1]=i*1.0;
  
   for(int i=0;i<Steps*N;++i)
     {
       X1[i]=0;  X2[i]=0;
     }

   for(int i=0;i<Steps;++i)
     Avg[i]=0;
     
   //////////////////////////////////////////////////////////////////////////////////////
   //Creo algoritmo que permite generar numeros aleatorios
   
   std::random_device rd;  //Will be used to obtain a seed for the random number engine
   //  int seed=8;
   //  std::mt19937 gen(seed);
   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_real_distribution<> dis(0.0,  1.0);

   //////////////////////////////////////////////////////////////////////////////////////
   // Inicio funcion que calcula el camino aleatorio en dos dimensions
   
   for(int i=0;i<N;++i)// bucle que realiza diferentes caminos
     {
       for(int j=0;j<Steps-1;++j)// Bucle que da cada paso aleatorio
	 {
	   random=dis(gen); // Se genera numero aleatorio 

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
	   //Actualizo las posiciones y las guardo en dos arreglos 

	   X1[j+1+i*Steps]=x1+X1[j+i*Steps];
	   X2[j+1+i*Steps]=x2+X2[j+i*Steps];
	   x1=0;
	   x2=0;
	   max_vec=dim*2;
	 }
     }

   //Se imprime cada punto del camino realzado y su respectivo calor r^2
   
    for(int i=0;i<pasos;++i)
     {
       for(int j=i;j<Steps*N;j+=Steps)
	 {
	   Avg[i]+=X1[j]*X1[j]+X2[j]*X2[j];
	 }
       printf(" %5d %7.3f ",contador,Avg[i]*1.0/N);
       contador++;

       for(int j=i;j<Steps*N;j+=Steps)
	 printf(" %4d %4d ",X1[j],X2[j]);

       printf("\n");
	 
     }
// std::cout << '\n';

     // delete [] X;
     // delete [] Y;
     // delete [] Avg;

   delete [] part;//sectores que se divide la unidad
   delete [] X1;
   delete [] X2;
   delete [] Avg; //Valor promedio de la posicion
 // printf(" %d ",pasos);
   
 return 0;
}

