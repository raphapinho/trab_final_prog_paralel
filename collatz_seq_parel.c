#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000
#define MAX_ITERACOES 1000

double collts_seq(void) {
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

  return elapsed_time;
}

double collatz_paral(void) {

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

  return elapsed_time;

  //Speedup = Tseq / Tpar
  //Eficiência = (Speedup / N) * 100%  #N é o número de processadores ou núcleos utilizados.
  //Desempenho = Trabalho Total / Tempo Total
}

int main(void){

    double time_seq = collts_seq();
    double time_paralel = collatz_paral();

    double speedup = time_seq /time_paralel;

    double eficiencia = (speedup/6) * 100;

    printf("o speedup é de %3.4f \n", speedup);

    printf("A eficiencia é de %3.4f \n", eficiencia);

    return 0;
}