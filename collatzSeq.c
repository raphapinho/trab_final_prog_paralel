#include <stdio.h>
#include <time.h>

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

    for (int i = 0; i < N; i++) {
        int numTeste = i + 1;

        for (int iters = 0; iters < MAX_ITERACOES && numTeste != 4; iters++) {
            numTeste = (numTeste % 2 == 1) ? (numTeste * 3) + 1 : numTeste / 2;
        }

        convergiu[i] = (numTeste == 4);
    }

    double end_time = get_wall_time();
    double elapsed_time = end_time - start_time;

    printf("Tempo de execucao: %.9f segundos\n", elapsed_time);

    return 0;
}
