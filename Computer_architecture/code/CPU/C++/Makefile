# Compiler definition
CC = g++

# Compiler flags for OpenMP and O3 optimization
CFLAGS = -O3 -fopenmp

# Name of the executable
TARGET = matrix_bash

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET).exe $(CFLAGS)

clean:
	rm -f $(TARGET).exe