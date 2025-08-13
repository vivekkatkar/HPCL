#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SIZE 10000000

int main() {
    int *a = (int*) malloc(SIZE * sizeof(int));
    int *b = (int*) malloc(SIZE * sizeof(int));
    int scalar = 10;

    for (int i = 0; i < SIZE; i++)
        a[i] = i;

    for (int threads = 1; threads <= 12; threads++) {
        omp_set_num_threads(threads);

        double start = omp_get_wtime();

        #pragma omp parallel for
        for (int i = 0; i < SIZE; i++)
            b[i] = a[i] + scalar;

        double end = omp_get_wtime();

        printf("Time taken with %2d threads: %f seconds\n", threads, end - start);
    }
    return 0;
}

// Barrier -> 
/*

*/