#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <windows.h> // For the SetThreadAffinityMask TESTTTTTTTT

using namespace std;
using namespace std::chrono;

#define BLOCK_SIZE 32

// The function that each thread executes (Workload)
void multiply_tiled_worker(int thread_id, int num_threads, int N, const double* A, const double* B, double* C) {
    // Calculate the range (rows) that this thread is responsible 
    for int rows_per_thread = N / num_threads;
    int row_start = thread_id * rows_per_thread;
    int row_end = (thread_id == num_threads - 1) ? N : row_start + rows_per_thread;

    // Tiling logic (Like the optimized code)
    for (int ii = row_start; ii < row_end; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
                
                for (int i = ii; i < min(ii + BLOCK_SIZE, row_end); i++) {
                    for (int k = kk; k < min(kk + BLOCK_SIZE, N); k++) {
                        double a = A[i * N + k];
                        for (int j = jj; j < min(jj + BLOCK_SIZE, N); j++) {
                            C[i * N + j] += a * B[k * N + j];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: <Threads> <N> <Mode 0:BASH/1:USER>" << endl;
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);
    int mode = atoi(argv[3]);

    vector<double> A(N * N, 1.5);
    vector<double> B(N * N, 2.0);
    vector<double> C(N * N, 0.0);

    vector<thread> threads;
    auto start = high_resolution_clock::now();

// Create Threads and apply Affinity (as your teammate did)    
        for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(multiply_tiled_worker, i, num_threads, N, A.data(), B.data(), C.data());

// Pin each thread to a specific core (Affinity)        
        DWORD_PTR mask = (DWORD_PTR)1 << (i % 20); // 20 cores
        SetThreadAffinityMask((HANDLE)threads.back().native_handle(), mask);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (mode == 1) {
        cout << "Manual Affinity Version - Threads: " << num_threads << " - Time: " << duration.count() << " ms" << endl;
    } else {
        cout << duration.count() << endl;
    }

    return 0;
}