#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <algorithm> 
#include <cstdlib>  

using namespace std;
using namespace std::chrono;

#define BLOCK_SIZE 32

void multiply_optimized(int N, const vector<double>& A,
                        const vector<double>& B,
                        vector<double>& C) {

    #pragma omp parallel for collapse(2) schedule(static)
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

    int N = 2048;
    int threads = 1;

    if (argc > 1) {
        threads = atoi(argv[1]);
    }
    if (argc > 2) {
        N = atoi(argv[2]);
    }

    omp_set_num_threads(threads);

 
    vector<double> A(N*N, 1.5);
    vector<double> B(N*N, 2.0);
    vector<double> C(N*N, 0.0);

    auto start = high_resolution_clock::now();

    multiply_optimized(N, A, B, C);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << duration.count() << endl;

    return 0;
}