#!/bin/bash

echo "Step 1: Compiling the codes..."
# Κάνουμε compile όλα τα .cpp αρχεία και τους δίνουμε τα σωστά ονόματα για τα .exe
g++ -O3 project_arch_og.cpp -o matrix_arch_og.exe
g++ -O3 -fopenmp project_arch_2.cpp -o matrix_arch_2.exe
g++ -O3 -fopenmp project_arch_3.cpp -o matrix_arch_3.exe
g++ -O3 -fopenmp optimised_gpt.cpp -o matrix_optimised_gpt.exe

echo "Step 2: Creating CSV files..."
echo "num_threads,matrix_size,execution_time_ms" > results_og.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch2.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch3.csv
echo "num_threads,matrix_size,execution_time_ms" > results_optimised.csv

echo "Running OG (Serial - this will take a while)..."
# Sending only threads (1) and size (2048)
time_og=$(./matrix_arch_og.exe 1 2048)
echo "1,2048,$time_og" >> results_og.csv

echo "Running Arch2..."
for t in {1..20}; do
   time_arch2=$(./matrix_arch_2.exe $t 2048)
   echo "$t,2048,$time_arch2" >> results_arch2.csv
done

echo "Running Arch3..."
for t in {1..20}; do
   time_arch3=$(./matrix_arch_3.exe $t 2048)
   echo "$t,2048,$time_arch3" >> results_arch3.csv
done

echo "Running Optimised..."
for t in {1..20}; do
   time_opt=$(./matrix_optimised_gpt.exe $t 2048)
   echo "$t,2048,$time_opt" >> results_optimised.csv
done

echo "DONE! All CSV files are ready."