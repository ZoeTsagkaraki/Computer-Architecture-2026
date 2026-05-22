# Matrix Multiplication Optimization

## Overview

This repository houses a comprehensive Computer Architecture project for the 2025/2026 academic year at the University of Pisa, focusing on the implementation, profiling, and optimization of the Matrix Multiplication algorithm. The project exclusively explores CPU-based approaches, leveraging parallel computing techniques and memory hierarchy optimizations to drastically enhance performance. It includes initial serial, naive parallel, and highly optimized versions of the algorithm implemented in C++ using OpenMP. The project also features detailed performance analyses, scalability studies, Intel VTune profiling insights, and Python scripts for benchmarking.

## Project Structure

The project is organized into the following directories:

* **`Code/`**: Contains all the source code for the project.
    * **`C++/`**: C++ source code for the CPU-based implementations.
        * `project_arch_og.cpp`: Initial serial baseline version of the matrix multiplication algorithm ($O(N^3)$).
        * `project_arch_2.cpp`: First parallel version utilizing OpenMP for naive loop distribution across threads.
        * `project_arch_3.cpp`: Intermediate optimized version exploring loop interchange (i-k-j) for better access patterns.
        * `optimised.cpp`: The final, highly optimized version utilizing 1D contiguous memory allocation, Cache Blocking (Tiling with `BLOCK_SIZE 32`), and SIMD vectorization.
    * **`Python/`**: Python scripts for performance and scalability analysis.
        * `generate_plots.py`: Automated script to parse benchmark CSVs and generate execution time, speed-up, and VTune microarchitecture usage charts.

* **`Data/`**: Contains the raw benchmark datasets generated during testing.
    * `matrix_results_arch2.csv`: Execution times and speed-up data for the naive parallel implementation.
    * `matrix_results_optimised.csv`: Execution times and speed-up data for the final optimized implementation.

* **`Insights/`**: Insights obtained from analyzing the CPU implementations.
    * `vtune_profiling/`: Screenshots and hotspot analyses from Intel VTune Profiler, demonstrating the resolution of the "Memory Wall" (Cache Thrashing) and the improvement in Microarchitecture Usage.

* **`Slides/`**: Contains slides for the project presentation.
    * `Matrix_Optimization_Presentation.pdf` / `.pptx`: Current presentation slides detailing the hardware ecosystem (Intel Core i7-12700H), the optimization strategy, and the final results.

## Authors
* **Maria Tsouktoridou**
* **Zoi Tsagkaraki**

*University of Pisa - Master Degree in Computer Engineering*
