#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
using namespace std;

void vector_add_static(vector<int> &A, int scalar, int chunk_size, int threads) {
    int n = A.size();
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(static, chunk_size) num_threads(threads)
    for (int i = 0; i < n; ++i) {
        A[i] += scalar;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "STATIC | Chunk: " << chunk_size << " | Threads: " << threads << " | Time: " << diff.count() << " sec\n";
}

void vector_add_dynamic(vector<int> &A, int scalar, int chunk_size, int threads) {
    int n = A.size();
    auto start = chrono::high_resolution_clock::now();

    #pragma omp parallel for schedule(dynamic, chunk_size) num_threads(threads)
    for (int i = 0; i < n; ++i) {
        A[i] += scalar;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "DYNAMIC | Chunk: " << chunk_size << " | Threads: " << threads << " | Time: " << diff.count() << " sec\n";
}

void demonstrate_nowait(vector<int> &A, vector<int> &B, int scalar) {
    int n = A.size();
    cout << "\nDemonstrating `nowait` clause:\n";
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for nowait
        for (int i = 0; i < n; ++i) {
            A[i] += scalar;
        }

        #pragma omp for
        for (int i = 0; i < n; ++i) {
            B[i] += scalar;
        }

        #pragma omp single
        cout << "Both loops are run in parallel without waiting between them (using `nowait`).\n";
    }
}

int main() {
    int size = 200;
    int scalar = 5;
    vector<int> A(size, 1);
    vector<int> B(size, 2);

    for (int threads : {2, 4, 8}) {
        for (int chunk_size : {1, 10, 20, 50}) {
            vector<int> vec_static = A;
            vector_add_static(vec_static, scalar, chunk_size, threads);

            vector<int> vec_dynamic = A;
            vector_add_dynamic(vec_dynamic, scalar, chunk_size, threads);
        }
    }

    demonstrate_nowait(A, B, scalar);

    return 0;
}
