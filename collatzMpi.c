#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

int collatz_conjecture(int n) {
    int iterations = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        iterations++;
    }
    return iterations;
}

void distribute_iterations(int total_iterations, int rank, int size, int *start_iteration, int *end_iteration) {
    int iterations_per_process = total_iterations / size;
    int extra_iterations = total_iterations % size;

    *start_iteration = rank * iterations_per_process + (rank < extra_iterations ? rank : extra_iterations);
    *end_iteration = *start_iteration + iterations_per_process + (rank < extra_iterations ? 1 : 0);
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time, end_time;

    int total_iterations = 100000;
    int start_iteration, end_iteration;
    distribute_iterations(total_iterations, rank, size, &start_iteration, &end_iteration);

    int local_iterations = end_iteration - start_iteration;
    int *local_results = (int *) malloc(local_iterations * sizeof(int));

    start_time = get_time();

    for (int i = start_iteration; i < end_iteration; i++) {
        int n = i + 1;
        int iterations = collatz_conjecture(n);
        local_results[i - start_iteration] = iterations;
    }

    int *results = NULL;
    if (rank == 0) {
        results = (int *) malloc(total_iterations * sizeof(int));
    }

    MPI_Gather(local_results, local_iterations, MPI_INT, results, local_iterations, MPI_INT, 0, MPI_COMM_WORLD);

    end_time = get_time();

    if (rank == 0) {
        //printf("Conjectura de Collatz com %d iterações:\n", total_iterations);
        for (int i = 0; i < total_iterations; i++) {
            //printf("Iteração %d: %d iterações\n", i + 1, results[i]);
        }
        free(results);
    }

    free(local_results);

    double execution_time = end_time - start_time;
    printf("Tempo de execução: %f\n", execution_time);

    MPI_Finalize();
    return 0;
}

/*
    compilar: mpicc -o collatzMpi collatzMpi.c
    executar: mpirun -np 4 ./collatzMpi
*/