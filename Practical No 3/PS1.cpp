#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <omp.h>
using namespace std;

#define SIZE 1000000

int main() {
    vector<int> A(SIZE), B(SIZE);

    // Initialize vectors with random integers
    for (int i = 0; i < SIZE; ++i) {
        A[i] = rand() % 1000;
        B[i] = rand() % 1000;
    }

    // Sort A in ascending and B in descending order
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());

    cout << "Thread\tTime(s)\t\tMin Scalar Product\n";

    for (int threads = 1; threads <= 12; ++threads) {
        long long min_dot = 0;
        omp_set_num_threads(threads);

        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:min_dot) schedule(static)
        for (int i = 0; i < SIZE; ++i) {
            min_dot += (long long)A[i] * B[i];
        }
        double end = omp_get_wtime();
        cout << threads << "\t" << (end - start) << "\t\t" << min_dot << "\n";
    }
    return 0;
}
