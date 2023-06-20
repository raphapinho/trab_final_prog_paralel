#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000
#define MAX_ITERACOES 1000

int main(void) {
  int convergiu[N] = {0};

  double start_time = omp_get_wtime();

#pragma omp parallel for
  for (int i = 0; i < N; i++) {
    int numTeste = i + 1;
    int iters = 0;

    do {
      iters++;
      numTeste = (numTeste % 2 == 1) ? (numTeste * 3) + 1 : numTeste / 2;

      if (numTeste == 4) {
        convergiu[i] = 1;
      }

    } while (numTeste != 4 && iters < MAX_ITERACOES);
  }

  double end_time = omp_get_wtime();
  double elapsed_time = end_time - start_time;

/*
  for (int i = 0; i < N; i++) {
    printf("Número %d %s.\n", i + 1,
           convergiu[i] ? "convergiu" : "não convergiu");
  }
*/

  printf("Tempo de execucao: %.6f segundos\n", elapsed_time);

  return 0;
}