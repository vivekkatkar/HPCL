#include <stdio.h>
#include <omp.h>

int main() {

    int threads;
    printf("Entire count of thread: ");
    scanf("%d", &threads);

    omp_set_num_threads(threads);

    for (int i = 0; i < threads; i++) {
        printf("Hello World from thread %d out of %d threads (sequential).\n", i, threads);
    }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello World from thread %d out of %d threads (parallel).\n", thread_id, total_threads);
        
    }
    return 0;
}



