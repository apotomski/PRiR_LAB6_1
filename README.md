# PRiR_LAB6_1

Projekt 1 z laboratoriów numer 6 z PRiR. Program oblicza przybliżenie liczby pi wykorzystując wzór Lebinz'a. Program został napisany w jęcyku c z wykorzystaniem MPI aby można było
obliczenia wykonać na wątkach(.

Opis kodu:

Import potrzebnych bibliotek

    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include "mpi.h"
    
FUnkcja obliczająca przybliżenie liczby pi na podstawie wzoru Lebinz'a. Na początku wartość jest dzielona przez 4 ponieważ wysyłana wartość do funkcji jest wartością wyliczoną dla poprzedniego wątku zaś tu w programie każdy wątek dodaje dla poprzedniej sumy odpowiednią wartość która jest pomnożona przez 4 temu na początku jest dzielenie ale na koniec wynik ponownie jest mnożony prze 4 ponieważ wymaga tego wzór.
    
    double Lebinz(int n, double wartosc) {
      double wynik = 0, tmp;
      double licznik, mianownik;
      wartosc = wartosc / 4;

      licznik = powf(-1, n-1);
      mianownik 2 * n - 1;
      wynik = licznik / mianownik;

      return 4 * (wartosc + wynik);
    }
    
funkcja main inicjalizuje MPI ustawia zmienne i sprawdza który aktulnie jest wątek. jeśli wątek jest = 0 to wysyła wynik do procesu 1. Dla pozostałych procesów > 1 i < n-1 odbierana jest wysłana zmienna z procesu o 1 mniejszego obliczane jest przybliżenie liczby pi wyświetlane i jeśli proces nie jest = n-1 to wartość przybliżenie jest wysyłana do procesu o 1 większego, w przeciwnym przypadku wyświetlany jest ostateczny wynik dla ostatniego procesu.

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
