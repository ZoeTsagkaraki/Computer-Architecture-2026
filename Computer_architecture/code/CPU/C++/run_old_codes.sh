#!/bin/bash

echo "Βήμα 1: Κάνω Compile τους κώδικες..."
g++ -O3 project_arch_og.cpp -o og.exe
g++ -O3 -fopenmp project_arch_2.cpp -o arch2.exe
g++ -O3 -fopenmp project_arch_3.cpp -o arch3.exe

echo "Βήμα 2: Φτιάχνω τα CSV αρχεία..."
echo "num_threads,matrix_size,execution_time_ms" > results_og.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch2.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch3.csv

echo "Τρέχω τον OG (Σειριακός - θα αργήσει λίγο)..."
time_og=$(./og.exe 1 2048 0)
echo "1,2048,$time_og" >> results_og.csv

echo "Τρέχω τον Arch2..."
for t in 1 2 4 8 16 20; do
   time_arch2=$(./arch2.exe $t 2048 0)
   echo "$t,2048,$time_arch2" >> results_arch2.csv
done

echo "Τρέχω τον Arch3..."
for t in 1 2 4 8 16 20; do
   time_arch3=$(./arch3.exe $t 2048 0)
   echo "$t,2048,$time_arch3" >> results_arch3.csv
done

echo "ΤΕΛΟΣ! Τα δεδομένα σώθηκαν στα CSV αρχεία."
