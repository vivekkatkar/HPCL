#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void matrix_add(int size, int threads) {
    vector<vector<int>> A(size, vector<int>(size));
    vector<vector<int>> B(size, vector<int>(size));
    vector<vector<int>> C(size, vector<int>(size));

    // Initialize matrices
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }

    omp_set_num_threads(threads);

    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            C[i][j] = A[i][j] + B[i][j];

    double end = omp_get_wtime();

    cout << "Matrix Size: " << size << "x" << size
         << " | Threads: " << threads
         << " | Time: " << (end - start) << " sec" << endl;
}

int main() {
    vector<int> sizes = {250, 500, 750, 1000, 2000};
    vector<int> threads = {1, 2, 4, 8};

    for (int size : sizes) {
        for (int t : threads) {
            matrix_add(size, t);
        }
        cout << endl;
    }

    return 0;
}
