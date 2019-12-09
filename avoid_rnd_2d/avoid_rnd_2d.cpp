#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>

// double desplazamiento();
 
int main()
{
  int N=100;//Repeticiones
  
  int Steps=100;
  int pasos=Steps;//Variable utilizada para  parar el programa si el camino aleatorio se encuentra con un punto sin salida posible.
  int dim=2;//Dimension del programa
  int contador=0;//Cuenta los pasos que se van realizando
  int max_vec=dim*2; //Cantidad maxima de vecinos que puede tener cada punto
  double random=0.0;

  int part[max_vec];//sectores que se divide la unidad
  //  int Position[N*Steps*2];//Guarda la posicion de los puntos utilizados
  //int XY[Steps*dim+1];
  int x1=0,x2=0;//Variables temporales
  int X1[Steps*N];
  int X2[Steps*N];
  int Avg[Steps]; //Valor promedio de la posicion
   
  // int *X= new int[N+1];
  // int *Y= new int[N+1];
  // int *Avg= new int[Steps+1]; //Valor promedio de la posicion
  // for(int i=0;i<=Steps;++i)
  //   for(int j=0;j<dim;++j)
  //     XY[i][j]=0;

  for(int i=1;i<=max_vec;++i)
    part[i-1]=i*1.0;
  
   for(int i=0;i<Steps*N;++i)
     {
       X1[i]=0;  X2[i]=0;
     }

   for(int i=0;i<Steps;++i)
     Avg[i]=0;
     
   
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    //  int seed=8;
    //  std::mt19937 gen(seed);
      std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
   std::uniform_real_distribution<> dis(0.0,  1.0);

   for(int i=0;i<N;++i)
     {
       // printf("%5d",n);
       for(int j=0;j<Steps-1;++j)
	 {

	   for(int i=1;i<=max_vec;++i)
	     part[i-1]=i*1.0;
       
	   random=dis(gen);
       
	   ////////////////////////////////////////////
	   for(int k=0;k<j;k++)
	     {
	       if(X2[j+i*Steps]==X2[k+i*Steps])//Reviso si la posicion j-esima de X2 ya esta ocupada en otra posicion k-esima
		 {
		   if(X1[j+i*Steps]+1==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps]) //Reviso si la posicion siguiente a X1 de j corresponde a la poscion k-esima de X1 (con esto comparo las parejas (X1[j]+1,X2[j]) y la posicion ya ocupada (X1[k],X2[k]) )
		     {
		       part[0]=0.0;
		       max_vec--;
		     }
		   if(X1[j+i*Steps]-1==X1[k+i*Steps] && X2[j+i*Steps]==X2[k+i*Steps])
		     {
		       part[1]=0.0;
		       max_vec--;
		     }
		 }

	       if(X1[j+i*Steps]==X1[k+i*Steps])
		 {
		   if(X2[j+i*Steps]+1==X2[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps])
		     {
		       part[2]=0.0;
		       max_vec--;
		     }
		   if(X2[j+i*Steps]-1==X2[k+i*Steps] && X1[j+i*Steps]==X1[k+i*Steps])
		     {
		       part[3]=0.0;
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

       /////////////////////////////////////////////////////////

       
       if(random<part[0]*1.0/max_vec){//el 0.5/dim se debe a que la cantidad de vecinos que tiene cada punto cuando maximo es dos veces la dimension 1/(2*dim)
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
       //XY[j+1][0]=X[i]+XY[j][0];
       //XY[j+1][1]=Y[i]+XY[j][1];
       X1[j+1+i*Steps]=x1+X1[j+i*Steps];
       X2[j+1+i*Steps]=x2+X2[j+i*Steps];
       x1=0;
       x2=0;
       max_vec=dim*2;
     }
   }

 for(int i=0;i<pasos;++i){
   for(int j=i;j<Steps*N;j+=Steps){
     printf(" %4d %4d ",X1[j],X2[j]);
     Avg[i]+=X1[j]*X1[j]+X2[j]*X2[j];
   }
   printf("%7.3f %5d \n",Avg[i]*1.0/N,contador);
   contador++;
 }
// std::cout << '\n';

     // delete [] X;
     // delete [] Y;
     // delete [] Avg;
 // printf(" %d ",pasos);
 return 0;
}

// double desplzamiento(){
//   return 0;
// }
