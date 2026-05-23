#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

#define BLOCK_SIZE 32


void multiply_optimized(int N, const vector<double>& A,
                        const vector<double>& B,
                        vector<double>& C) {

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {

            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {

                for (int i = ii; i < min(ii + BLOCK_SIZE, N); i++) {
                    for (int k = kk; k < min(kk + BLOCK_SIZE, N); k++) {

                        double a = A[i*N + k];

                        #pragma omp simd
                        for (int j = jj; j < min(jj + BLOCK_SIZE, N); j++) {
                            C[i*N + j] += a * B[k*N + j];
                        }
                    }
                }

            }
        }
    }
}

int main(int argc, char* argv[]) {
    int threads = stoi(argv[1]);
    int N = stoi(argv[2]);

    omp_set_num_threads(threads);

    cout << "Allocating memory..." << endl;

  
    vector<double> A(N*N, 1.5);
    vector<double> B(N*N, 2.0);
    vector<double> C(N*N, 0.0);

    cout << "Starting optimized computation..." << endl;

    auto start = high_resolution_clock::now();

    multiply_optimized(N, A, B, C);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Execution time: " << duration.count() << " ms" << endl;

    cout << "Checking correctness..." << endl;

    double expected = N * 1.5 * 2.0;
    bool correct = true;

    for (int i = 0; i < N*N; i++) {
        if (C[i] != expected) {
            correct = false;
            break;
        }
    }

    if (correct)
        cout << "SUCCESS: matrix is correct" << endl;
    else
        cout << "ERROR: wrong result" << endl;

    return 0;
}