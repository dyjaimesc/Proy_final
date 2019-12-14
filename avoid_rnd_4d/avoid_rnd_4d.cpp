//Programa que realiza el self avoiding walk en 3d

#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include<fstream>

int lectura();//Funcion que lee la dimension del bloque
// double desplazamiento();
 
int main()
{
  //Se crean variables que  dan la cantidad de caminos que se realzan (N) y la cantidad de pasos por camino (Steps)
  int N=200;//Repeticiones
  int Steps=50;

  int pasos=Steps;//Variable utilizada para  parar el programa si el camino aleatorio se encuentra con un punto sin salida posible.
  int dim=4;//Dimension del programa
  int contador=0;//Cuenta los pasos que se van realizando
  int max_vec=dim*2; //Cantidad maxima de vecinos que puede tener cada punto
  double random=0.0;
  int x1=0,x2=0,x3=0,x4=0;//Variables temporales donde guardo los cambios de las respectivas coordenads

  // int part[max_vec];//sectores que se divide la unidad
  //int X1[Steps*N];
  //  int X2[Steps*N];
  //  int X3[Steps*N];
  //  int Avg[Steps]; //Valor promedio de la posicion

  int *part= new int[max_vec];//sectores que se divide la unidad
  int *X1= new int[Steps*N];
  int *X2= new int[Steps*N];
  int *X3= new int[Steps*N];
  int *X4= new int[Steps*N];
  int *Avg= new int[Steps]; //Valor promedio de la posicion
  
  ///////////////////////////////////////////////////////////////////////////////////////
  //Inicializo los arreglos que se van a utilizar
  
  for(int i=1;i<=max_vec;++i)
    part[i-1]=i*1.0;
  
   for(int i=0;i<Steps*N;++i)
     {
       X1[i]=0;  X2[i]=0; X3[i]=0; X4[i]=0;
     }

   for(int i=0;i<Steps;++i)
     Avg[i]=0;
     
   //////////////////////////////////////////////////////////////////////////////////////
   //Algoritmo que permite generar numeros aleatorios
   
   // std::random_device rd;  //Will be used to obtain a seed for the random number engine
   int seed=lectura();
      std::mt19937 gen(seed);
      // std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_real_distribution<> dis(0.0,  1.0);

   //////////////////////////////////////////////////////////////////////////////////////
   // Inicio funcion que calcula el camino aleatorio en tres dimensions
   
   for(int i=0;i<N;++i)// bucle que realiza diferentes caminos
     {
       for(int j=0;j<Steps-1;++j)// Bucle que da cada paso aleatorio
	 {
	   random=dis(gen); // Se genera numero aleatorio
	   
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
	   else if(random<part[6]*1.0/max_vec){
	     x4+=1;
	   }
	   else if(random<part[7]*1.0/max_vec){
	     x4-=1;
	   }
	   //Actualizo las posiciones y las guardo en dos arreglos 

	   X1[j+1+i*Steps]=x1+X1[j+i*Steps];
	   X2[j+1+i*Steps]=x2+X2[j+i*Steps];
	   X3[j+1+i*Steps]=x3+X3[j+i*Steps];
	   X4[j+1+i*Steps]=x4+X4[j+i*Steps];
	   x1=0;
	   x2=0;
	   x3=0;
	   x4=0;
	   max_vec=dim*2;

	   ///////////////////////////////////////////////////////////////////
	   // Algoritmo que verifica puntos recorridos

	   for(int k=0;k<j;k++)
	     {
	       if(X1[j+i*Steps]==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps] && X3[j+i*Steps]==X3[k+i*Steps] && X4[j+i*Steps]==X4[k+i*Steps])//Reviso si la posicion j-esima de X2 ya esta ocupada en otra posicion k-esima
		 {
		   j=0;//Reinicio el camino.
		   break;
		 }
	     }


	   
	 }
     }

   //Se imprime cada punto del camino realzado y su respectivo calor r^2
   
   for(int i=0;i<pasos;++i)
     {
       for(int j=i;j<Steps*N;j+=Steps)
	 {
	   // printf(" %4d %4d %4d ",X1[j],X2[j],X3[j]);
	   Avg[i]+=X1[j]*X1[j]+X2[j]*X2[j]+X3[j]*X3[j]+X4[j]*X4[j];
	 }
       printf(" %5d %7.3f ",contador,Avg[i]*1.0/N);
       contador++;

       for(int j=i;j<Steps*N;j+=Steps)
	 printf(" %4d %4d %4d %4d",X1[j],X2[j],X3[j],X4[j]);

       printf("\n");
	 
     }

   delete [] part;//sectores que se divide la unidad
   delete [] X1;
   delete [] X2;
   delete [] X3;
   delete [] X4;
   delete [] Avg; //Valor promedio de la posicion
 
   
 return 0;
}

int lectura(){
  int x=0;//Variable para guardar  el numero del bloque que viene dado del un archivo de texto externo creado en el script
  int Longitud_cadena=0;
  char buffer[6];   //Creo una variable char para guardar renglon a renglon cada uno de los renglones de los datos
  char temporal[6];
  
  std::ifstream archivo;
  std::string texto;
  archivo.open("entrada.dat",std::ios::in);
  if(archivo.fail()){
    printf("No se pudo abrir el archivo");
  }

  while(!archivo.eof()){//Mientras no sea el final del archivo
    getline(archivo,texto,'\n');
    Longitud_cadena=texto.length();
    size_t length = texto.copy(buffer,Longitud_cadena,0);   //convierto el string en char, y guardo la longitud del char en length
    buffer[length]='\0';    //despues de terminar los caracteres de mi char dejo vacia la siguiente casilla
    length=texto.copy(temporal,Longitud_cadena,0);
    x=std::atoi(temporal);
  }
  archivo.close();
  return x;
}
