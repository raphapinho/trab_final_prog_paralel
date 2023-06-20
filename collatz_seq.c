#include <stdio.h>
#include <stdlib.h>

#include <omp.h> //usado somente para pegar o tempo de execução

#define N 100000
#define MAX_ITERACOES 1000

int main(void) {

    double start_time = omp_get_wtime();

  int convergiu[N], i;

  for (i = 0; i < N; i++) {
    convergiu[i] = 0;
  }

  for (i = 0; i < N; i++) {
   // printf("Testando %d.\n", i+1);
    int numTeste = i+1;
    int iters = 0;
    do {
      iters++;
      //printf("Iteração %d: %d é ", iters, numTeste);
      if (numTeste % 2 == 1) { // impar
        //printf("impar, 3x + 1.\n");
        numTeste = (numTeste * 3) + 1; // 3x + 1
      } else { // par
        //printf("par, x/2.\n");
        numTeste /= 2; // x/2
      }

      if (numTeste == 4) {
        //printf("%d convergiu.\n", i+1);
        convergiu[i] = 1;
      }
    } while (numTeste != 4 && iters < MAX_ITERACOES);
/*
    if (!convergiu[i]) {
      printf("%d não convergiu.\n", i+1);
    }
*/

    //printf("\n");
  }
/*
  for (i = 0; i < N; i++) {
    printf("Número %d %s.\n", i+1, convergiu[i] ? "convergiu" : "não convergiu");
  }
*/
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("Tempo de execucao: %.6f segundos\n", elapsed_time);

  return 0;
}