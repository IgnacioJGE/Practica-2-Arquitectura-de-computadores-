#include <iostream>

#include <mpi.h>

#include <string>

#include <cstring>

#include <fstream>

#include<unistd.h>

#include<time.h>

#include <stdlib.h>

using namespace std;
int main(int argc, char ** argv) {
  int rango, participantes, minum;
  int contador = 1;
  int bingo=57;
  int fin=3;
  int bing;
  bool alwaystrue = true;
  string linetext;
  MPI_Init( & argc, & argv); //inicialización entorno MPI
  MPI_Comm_rank(MPI_COMM_WORLD, & rango); //rango del proceso
  MPI_Comm_size(MPI_COMM_WORLD, & participantes);
  MPI_Request request; //variable de control

  ifstream archivo("Cartones.txt");

  if (rango == 0) {
    cout << "El numero de participantes es " << participantes - 1 << endl; //le resto uno porque el proceso 0 no cuenta como parrticipante
    sleep(2);
    while (alwaystrue) {
    MPI_Status status;
    int flag=0;
	MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag,&status);
    if(flag){
    MPI_Recv(&rango, 1, MPI_INT, MPI_ANY_SOURCE, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cout << "El ganador es el proceso "<< rango<< endl;
    fin=0;

    break;
    }else{
      bingo = 1 + rand() % (41 - 1);
      cout << bingo << endl;
      MPI_Bcast(&bingo, 1, MPI_INT, 0, MPI_COMM_WORLD);
      sleep(2.5);
    }
    }
    if(fin==0){
        MPI_Bcast(&fin, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
  } else {
    while (getline(archivo, linetext)) {

      if (rango == contador) {
        minum = stoi(linetext);

      }

      contador++;
    }
    while (alwaystrue) {
      MPI_Bcast(&bingo, 1, MPI_INT, 0, MPI_COMM_WORLD);

      if (minum == bingo) {
        cout << "BINGOOO!! soy el proceso " << rango << " y mi número es el " << minum << endl;
	MPI_Send(&rango, 1,MPI_INT, 0, 0, MPI_COMM_WORLD);
        break;
      }
    MPI_Status status;
    int flag=0;
    MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag,&status);
      if(flag){
break;
      }
    }
      
  }

  MPI_Finalize(); //fin entorno MPI
  return 0;
}
