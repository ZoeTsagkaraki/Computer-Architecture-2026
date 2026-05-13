#! /bin/bash

# Script for Matrix Multiplication measurements
if [ "$#" -ne 4 ]; then
    echo "Error: Illegal number of parameters, please provide:"
    echo " 1. Executable path"
    echo " 2. Number of iterations"
    echo " 3. Max number of threads"
    echo " 4. Matrix size (N)"
    exit 1
fi

EXECUTABLE=$1
NUM_ITERATIONS=$2
MAX_THREADS=$3
MATRIX_SIZE=$4

TIME=$(date +"%Y-%m-%d_%H-%M-%S")
OUTPUT_FILE="matrix_output_${TIME}.csv"

echo "Executing Matrix Multiplication Benchmark..."
echo "Executable: ${EXECUTABLE}"
echo "Iterations per thread: ${NUM_ITERATIONS}"
echo "Max threads: ${MAX_THREADS}"
echo "Matrix Size: ${MATRIX_SIZE}x${MATRIX_SIZE}"
echo ""

# Create CSV Header
echo "num_threads,iteration,matrix_size,execution_time_ms" > ${OUTPUT_FILE}

# Execute benchmark loop
for ((NUM_THREADS = 1; NUM_THREADS <= ${MAX_THREADS}; NUM_THREADS++)); do
    for ((i = 0; i < ${NUM_ITERATIONS}; i++)); do
        echo "Running iteration ${i} with ${NUM_THREADS} threads..."
        
        # Write constant data to CSV without a newline (-n)
        echo -n "${NUM_THREADS},${i},${MATRIX_SIZE}," >> ${OUTPUT_FILE}
        
        # Run the C++ program and append its output to the end of the line!
        ./${EXECUTABLE} ${NUM_THREADS} ${MATRIX_SIZE} 0 >> ${OUTPUT_FILE} 
    done
done

echo "Benchmark finished! Results saved in ${OUTPUT_FILE}"