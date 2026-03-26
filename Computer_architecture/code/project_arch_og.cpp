#include <iostream>
#include <vector>
#include <chrono> 

using namespace std;
using namespace std::chrono;

 

void multiply_2D_naive(int N, const vector<vector<double>>& A, 
                       const vector<vector<double>>& B, 
                       vector<vector<double>>& C) {
    
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int N = 2048; 

    cout << "Δέσμευση μνήμης για πίνακες " << N << "x" << N << "..." << endl;

    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N));

    cout << "Αρχικοποίηση πινάκων με χειροκίνητα loops..." << endl;

    
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


    auto start = high_resolution_clock::now();

    // Κλήση της συνάρτησης πολλαπλασιασμού
    multiply_2D_naive(N, A, B, C);

    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "The execution time is " << duration.count() << " milliseconds." << endl;


cout << "Γίνεται έλεγχος ορθότητας..." << endl;
    
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
