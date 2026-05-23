# Matrix Multiplication Optimization

## Overview

This repository houses a comprehensive Computer Architecture project for the 2025/2026 academic year at the University of Pisa, focusing on the implementation, profiling, and optimization of the Matrix Multiplication algorithm. The project exclusively explores CPU-based approaches, leveraging parallel computing techniques and memory hierarchy optimizations to drastically enhance performance. It includes initial serial, naive parallel, and highly optimized versions of the algorithm implemented in C++ using OpenMP. The project also features detailed performance analyses, scalability studies, Intel VTune profiling insights, and automated bash scripts for benchmarking.

## Project Structure

The project is organized into the following directories under `Computer_architecture/`:

* **`code/CPU/C++/`**: C++ source code for the CPU-based implementations.
    * `project_arch_og.cpp`: Initial serial baseline version of the matrix multiplication algorithm ($O(N^3)$).
    * `project_arch_2.cpp`: First parallel version utilizing OpenMP for naive loop distribution across threads (Memory-bound).
    * `optimised.cpp`: The highly optimized version utilizing 1D contiguous memory allocation, Cache Blocking (Tiling with `BLOCK_SIZE 32`), and SIMD vectorization.
    * `Manual_Affinity_Tiled_Matrix.cpp`: Final version analyzing the effects of L1 Cache Contention using Thread Affinity.
    * `Makefile`: Make rules for compiling the CPU implementations.

* **`code/CPU/bash/`**: Bash scripts for automated benchmarking.
    * `execute_matrix_threads.sh` / `execute_matrix_size.sh` / `run_all.sh`: Automated scripts to execute the binaries across varying thread counts and matrix sizes, outputting the results to CSV formats.

* **`code/CPU/Benchmarks/`**: Contains the raw benchmark datasets generated during testing.
    * Includes the CSV and Excel results detailing Execution Times, Speed-up data, and Efficiency across different architectures.

* **`intel_vtune/`**: Insights obtained from analyzing the CPU implementations.
    * `arch2/` & `optimised/`: Screenshots and hotspot analyses from Intel VTune Profiler, demonstrating the resolution of the "Memory Wall" (Cache Thrashing) and the improvement in Microarchitecture Usage.

* **`slides/`**: Contains slides for the project presentation.
    * `Matrix Multiplication Optimization.pdf`: Current presentation slides detailing the hardware ecosystem, the optimization strategy (Tiling & Affinity), and the final results.

## Authors
* **Maria Tsouktoridou**
* **Zoi Tsagkaraki**

*University of Pisa - Master Degree in Computer Engineering*