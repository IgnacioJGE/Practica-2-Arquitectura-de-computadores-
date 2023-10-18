#include <iostream>

#include <mpi.h>

#include <string>

#include <cstring>

#include <fstream>

#include<unistd.h>

#include<time.h>

using namespace std;
int main(int argc, char ** argv) {
  int rango, participantes, minum;
  int contador = 1;
  int bingo;
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
      bingo = 1 + rand() % (41 - 1);
      cout << bingo << endl;
      MPI_Bcast( & bingo, 1, MPI_INT, 0, MPI_COMM_WORLD);
      sleep(1.5);
    }

  } else {
    while (getline(archivo, linetext)) {

      if (rango == contador) {
        minum = stoi(linetext);

      }

      contador++;
    }
    while (alwaystrue) {
      MPI_Bcast( & bingo, 1, MPI_INT, 0, MPI_COMM_WORLD); // al estar dentro de bucles infinitos 			tengo que hacer un broadcast para enviar y otro para recibir
      if (minum == bingo) {
        cout << "BINGOOO!! soy el proceso " << rango << " y mi número es el " << minum << endl;
      }

    }
  }

  MPI_Finalize(); //fin entorno MPI
  return 0;
}
