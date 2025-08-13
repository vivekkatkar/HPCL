#include <stdio.h>
#include <omp.h>

int main() {
    long long num_steps = 100000000;
    double step = 1.0 / (double)num_steps;

    for (int threads = 1; threads <= 12; threads++) {
        double pi = 0.0;

        omp_set_num_threads(threads);
        double start = omp_get_wtime();

        #pragma omp parallel
        {
            double x, sum = 0.0;
            int id = omp_get_thread_num();
            int nthreads = omp_get_num_threads();

            for (long long i = id; i < num_steps; i += nthreads) {
                x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }
            pi += sum * step;
        }
        double end = omp_get_wtime();
        printf("Threads: %2d | Pi = %.15f | Time: %f seconds\n", threads, pi, end - start);
    }
    return 0;
}
