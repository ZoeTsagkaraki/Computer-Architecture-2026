#!/bin/bash

echo "Φτιάχνω τα CSV αρχεία..."
echo "num_threads,matrix_size,execution_time_ms" > results_og.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch2.csv
echo "num_threads,matrix_size,execution_time_ms" > results_arch3.csv
echo "num_threads,matrix_size,execution_time_ms" > results_optimised.csv

echo "Τρέχω τον OG (Σειριακός)..."
# Στέλνουμε μόνο threads (1) και μέγεθος (2048)
time_og=$(./matrix_arch_og.exe 1 2048)
echo "1,2048,$time_og" >> results_og.csv

echo "Τρέχω τον Arch2..."
for t in 1 2 4 8 16 20; do
   time_arch2=$(./matrix_arch_2.exe $t 2048)
   echo "$t,2048,$time_arch2" >> results_arch2.csv
done

echo "Τρέχω τον Arch3..."
for t in 1 2 4 8 16 20; do
   time_arch3=$(./matrix_arch_3.exe $t 2048)
   echo "$t,2048,$time_arch3" >> results_arch3.csv
done

echo "Τρέχω τον Optimised..."
for t in 1 2 4 8 16 20; do
   time_opt=$(./matrix_optimised_gpt.exe $t 2048)
   echo "$t,2048,$time_opt" >> results_optimised.csv
done

echo "ΤΕΛΟΣ! Όλα τα CSV είναι έτοιμα."