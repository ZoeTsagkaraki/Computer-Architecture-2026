#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h> // Necessary for Threads

using namespace std;
using namespace std::chrono;

// This directive tells the compiler to divide the outer 'i' loop 
// among multiple CPU threads for parallel execution.
void multiply_2D_naive(int N, const vector<vector<double>>& A,
                       const vector<vector<double>>& B,
                       vector<vector<double>>& C) {
   
#pragma omp parallel for
                       
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Standard i-j-k order
            }
        }
    }
}

int main() {
    int N = 2048;

    cout << "Allocating memory for matrices " << N << "x" << N << "..." << endl;

    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N));

    cout << "Initializing matrices with manual loops..." << endl;

   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1.5;
        }
    }

   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = 2.0;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0.0;
        }
    }

    cout << "The serial calculation starts ..." << endl;

    auto start = high_resolution_clock::now(); // Record the start time

    // Call the multiplication function
    multiply_2D_naive(N, A, B, C);

    auto stop = high_resolution_clock::now();
   
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "The execution time is " << duration.count() << " milliseconds." << endl;


cout << "Performing correctness check..." << endl;
   
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
        cout << "the matrix is correct" << endl;
    } else {
        cout << "the matrix has wrong numbers" << endl;
    }

    return 0;
}