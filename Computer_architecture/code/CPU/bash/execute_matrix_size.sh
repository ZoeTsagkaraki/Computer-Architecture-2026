#! /bin/bash

# (Matrix Size)
if [ "$#" -ne 5 ]; then
    echo "Error: Illegal number of parameters, please provide:"
    echo " 1. Executable path"
    echo " 2. Number of iterations"
    echo " 3. Number of threads"
    echo " 4. Max Matrix Size (N)"
    echo " 5. Step size"
    exit 1
fi

EXECUTABLE=$1
NUM_ITERATIONS=$2
NUM_THREADS=$3
MAX_SIZE=$4
STEP=$5

TIME=$(date +"%Y-%m-%d_%H-%M-%S")
OUTPUT_FILE="matrix_size_output_${TIME}.csv"

echo "num_threads,iteration,matrix_size,execution_time_ms" > ${OUTPUT_FILE}

for ((SIZE = ${STEP}; SIZE <= ${MAX_SIZE}; SIZE += ${STEP})); do
    for ((i = 0; i < ${NUM_ITERATIONS}; i++)); do
        echo "Running iteration ${i} for matrix size ${SIZE}x${SIZE}..."
        echo -n "${NUM_THREADS},${i},${SIZE}," >> ${OUTPUT_FILE}
        ./${EXECUTABLE} ${NUM_THREADS} ${SIZE} >> ${OUTPUT_FILE} 
    done
done

echo "Done! Saved in ${OUTPUT_FILE}"