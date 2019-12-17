//Programa que encuentra el promedio y la desviacion estandar de un conjunto de datos

#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>

double *datos;
int lectura();//Funcion que lee la dimension del bloque, retorna cantidad de lineas
double promedio(int); // ingreso valor cantidad de datos con las que voy a calcular el promedio

double desv_estandar(double,int);//para hallar la desviacion estandar ingreso el valor promedio de los datos y la cantidad de datos
 
int main()
{
  int n=lectura();
  double media=0, dvst=0;

  media=promedio(n);
  dvst=desv_estandar(media,n);

  printf("\n Valor del exponente alfa para semillas entre 1 y %d \n",n
	 );
  for(int i=0;i<n;i++)
    printf("%10.3f \n",datos[i]);

  printf("El promedio del exponente alfa para los %d datos es: %10.3f +/- %2.3f \n",n,media,dvst);
 
   delete [] datos;
   
 return 0;
}

/////////////////////////////////////////////////////////////////
// Lectura del .txt

int lectura(){
  
  int numLines = 0;
  std::ifstream in("Pendiente.txt");
  std::string unused;

  while (std::getline(in, unused)){
    ++numLines;
  }
  
  int tam=20;//Variable que me da el tamanho de los arreglos en los se guardan los char antes de convertirlos a numeros
  int Longitud_cadena=0;
  char buffer[tam];   //Creo una variable char para guardar renglon a renglon cada uno de los renglones de los datos
  char temporal[tam];
  // int n_f=0;  //contador de cuantas lineas se ha leido
  std::ifstream archivo;
  std::string texto;

  datos= new double[numLines];
  // double datos[numLines];
  // double datos=1.0;
  //  std::cout << numLines<<std::endl;
  // for(int i=0;i<numLines;i++)
  //   datos[i]=0.0;
    
  archivo.open("Pendiente.txt",std::ios::in);

  if(archivo.fail()){
    printf("No se pudo abrir el archivo");
    exit(1);
  }

  // while(!archivo.eof() && n_f<numLines)   //Mientras no sea el final del archivo (.eof)
  for(int i=0;i<numLines;++i)//Recorro todas las lineas atras contadas
  {
     getline(archivo,texto,'\n');    //Pongo mi primer renglon en el el string "texto"
		
     Longitud_cadena=texto.length(); //Mido la cantidad de caracteres que tiene cada string
     size_t length = texto.copy(buffer,Longitud_cadena,0);   //convierto el string en char, y guardo la longitud del char en length
     buffer[length]='\0';    //despues de terminar los caracteres de mi char dejo vacia la siguiente casilla
     length = texto.copy(temporal,Longitud_cadena,0);
     temporal[length]='\0';	
     datos[i]=atof(temporal);
     //  printf("%20.15f %5d \n",datos[i],i);
   }
  
  archivo.close();
  return numLines;
}

/////////////////////////////////////////////
/////Calculo en promedio de los datos que ingreso

double promedio(int N)
{
  //double media=0;
  double temporal=0; /// Variable temporal que me almacena la suma de todos los datos
   for(int i=0;i<N;i++)
     {
      temporal+= datos[i];
     }
   
  
  return temporal/N;
}

/////////////////////////////////////////////////////
//// Funcion que calcula la desviacion estandar

double desv_estandar(double media,int N)
{
  double sigma=0;

  for(int i=0;i<N;i++)
     {
      sigma+= datos[i]*datos[i]+media*media-2.0*datos[i]*media;
     }

  sigma/=(N-1.0);
  
  return sqrt(sigma);
}
