#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "mpi.h"

double Lebinz(int n, double wartosc) {
	double wynik = 0, tmp;
	double licznik, mianownik;
	wartosc = wartosc / 4;
	
	licznik = powf(-1, n-1);
	mianownik 2 * n - 1;
	wynik = licznik / mianownik;
	
	return 4 * (wartosc + wynik);
}

int main(int argc, char **argv) {
	int n, p, tag = 20;
	double wynik = 0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Status status;
	if(p == 0) {
		MPI_Send(&wynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
	} 
	if((p > 1) && (p < n-1)) {
		MPI_Recv(&wynik, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);
		wynik = Lebinz(p, wynik);
		printf("Proces = %d | Aktualny wynik = %lf", p, wynik);
		if(p != n-1) {
			MPI_Send(&wynik, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
		}
		else {
			printf("Proces = %d | Wynik = %lf", p, wynik);
		}
	}
	
	MPI_Finalize();
	return 0;
}