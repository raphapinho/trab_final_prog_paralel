#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define MAX_ITERACOES 1000

double get_wall_time() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + (double)time.tv_nsec * 1e-9;
}

int main(void) {
    int convergiu[N] = {0};

    double start_time = get_wall_time();

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

    double end_time = get_wall_time();
    double elapsed_time = end_time - start_time;

    printf("Tempo de execucao: %.9f segundos\n", elapsed_time);

  return 0;
}