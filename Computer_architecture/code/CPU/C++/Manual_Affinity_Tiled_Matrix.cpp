#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <windows.h> // Για το SetThreadAffinityMask

using namespace std;
using namespace std::chrono;

#define BLOCK_SIZE 32

// Η συνάρτηση που εκτελεί κάθε thread (Workload)
void multiply_tiled_worker(int thread_id, int num_threads, int N, const double* A, const double* B, double* C) {
    // Υπολογισμός του εύρους (rows) που αναλαμβάνει αυτό το thread
    int rows_per_thread = N / num_threads;
    int row_start = thread_id * rows_per_thread;
    int row_end = (thread_id == num_threads - 1) ? N : row_start + rows_per_thread;

    // Tiling logic (Όπως στον optimized κώδικά σου)
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

    // Δημιουργία Threads και εφαρμογή Affinity (όπως ο συμφοιτητής σου)
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(multiply_tiled_worker, i, num_threads, N, A.data(), B.data(), C.data());

        // Κλείδωμα κάθε thread σε έναν συγκεκριμένο πυρήνα (Affinity)
        DWORD_PTR mask = (DWORD_PTR)1 << (i % 20); // 20 είναι οι πυρήνες σου
        SetThreadAffinityMask((HANDLE)threads.back().native_handle(), mask);
    }

    // Αναμονή για να τελειώσουν όλα τα threads
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