#include <random>
#include <iostream>
#include <cstdio>

// double desplazamiento();
 
int main()
{
  int N=500;//Repeticiones
  
   int Steps=100;
   
   double x=0.0;

  int *X= new int[N+1];
  int *Avg= new int[Steps+1]; //Valor promedio de la posicion
  
   for(int i=0;i<=N;++i)
     {
       X[i]=0;
     }

   for(int i=0;i<=Steps;++i)
     {
       Avg[i]=0;
     }
   
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0,  1.0);

   
for (int n = 1; n <=Steps; ++n) {
  printf("%5d",n);

   for(int i=1;i<=N;++i)
   {
      if(dis(gen)>0.5){
	X[i]+=1;
	      }
      else{
	X[i]-=1;
      }
      
      printf(" %5d ",X[i]);
	
      //std::cout << dis(gen) << ' ';
      Avg[n]+=X[i]*X[i];
   }
  x=Avg[n]*1.0/N;

  printf(" %5.1f ",x);

  std::cout << '\n';
 }
// std::cout << '\n';

     delete [] X;
     delete [] Avg;
}

// double desplzamiento(){
//   return 0;
// }
