1/////
12th Gen Intel(R) Core(TM) i7-12700H

Cores: 14, Logical Processors: 20
L1d Cache (Data): 544 KB  
L1i Cache (Inst.): 704 KB
L2 Cache: 11.5 MB
L3 Cache: 24 MB
Base Frequency: 2.30 GHz
Max Turbo Frequency: 4.70 GHz

2/////
EXECUTION TIME:
auto start = chrono::high_resolution_clock::now();

multiply_optimized(N, A, B, C);

auto stop = chrono::high_resolution_clock::now();

auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

3/////
Matrix A (2048 x 2048) * Matrix B (2048 x 2048) = Matrix C
O(N³) ≈ 8.5 Billion Operations
#THREADS : 1 (Serial)
execution time=19626 ms =20 seconds UNOPTIMIZED


