#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h> // Necessary for Threads

using namespace std;
using namespace std::chrono;

// The optimized 2D function (Loop Interchange: i-k-j)
void multiply_2D_omp(int N, const vector<vector<double>>& A, 
                     const vector<vector<double>>& B, 
                     vector<vector<double>>& C) {
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {          
            for (int j = 0; j < N; j++) {      
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // We set N=2048 so the test finishes in a reasonable time (approx. 30-40 seconds in total)
    int N = 2048; 

    cout << "Allocating memory for 2D matrices (" << N << "x" << N << ")..." << endl;
    vector<vector<double>> A(N, vector<double>(N, 1.5));
    vector<vector<double>> B(N, vector<double>(N, 2.0));
    vector<vector<double>> C(N, vector<double>(N, 0.0));

    // The list with the number of threads we want to test
    vector<int> thread_counts = {1, 2, 4, 8, 12, 16, 20};

    cout << "\n--- Starting the Benchmark (Scalability Test) ---" << endl;

    for (int threads : thread_counts) {
        
        // 1. Set how many cores OpenMP will use
        omp_set_num_threads(threads);

        // 2. ZERO OUT matrix C (clear garbage from the previous run)
        for (int i = 0; i < N; i++) {
            fill(C[i].begin(), C[i].end(), 0.0);
        }

        // 3. Start the timer
        auto start = high_resolution_clock::now();
        
        multiply_2D_omp(N, A, B, C);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        // 4. Print the result with nice alignment
        cout << "Threads: " << threads << " \t| Time: " << duration.count() << " ms" << endl;
    }

    cout << "------------------------------------------------\n" << endl;

    // Correctness Check (checks the last run with 20 threads)
    bool is_correct = true;
    double expected_value = N * 1.5 * 2.0; 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (C[i][j] != expected_value) {
                is_correct = false;
                break; 
            }
        }
    }

    if (is_correct) {
        cout << "SUCCESS: The matrix was calculated correctly!" << endl;
    } else {
        cout << "ERROR: The matrix has wrong numbers!" << endl;
    }

    return 0;
}