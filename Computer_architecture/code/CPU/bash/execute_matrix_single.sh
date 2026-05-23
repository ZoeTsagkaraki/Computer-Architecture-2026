#! /bin/bash

# Script for a single configuration
if [ "$#" -ne 4 ]; then
    echo "Error: Illegal number of parameters, please provide:"
    echo " 1. Executable path"
    echo " 2. Number of iterations"
    echo " 3. Number of threads"
    echo " 4. Matrix Size (N)"
    exit 1
fi

EXECUTABLE=$1
NUM_ITERATIONS=$2
NUM_THREADS=$3
MATRIX_SIZE=$4

TIME=$(date +"%Y-%m-%d_%H-%M-%S")
OUTPUT_FILE="matrix_single_output_${TIME}.csv"

echo "num_threads,iteration,matrix_size,execution_time_ms" > ${OUTPUT_FILE}

for ((i = 0; i < ${NUM_ITERATIONS}; i++)); do
    echo "Running iteration ${i}..."
    echo -n "${NUM_THREADS},${i},${MATRIX_SIZE}," >> ${OUTPUT_FILE}
    ./${EXECUTABLE} ${NUM_THREADS} ${MATRIX_SIZE} >> ${OUTPUT_FILE} 
done

echo "Done! Saved in ${OUTPUT_FILE}"