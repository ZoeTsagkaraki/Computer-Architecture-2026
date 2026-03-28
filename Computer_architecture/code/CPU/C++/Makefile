# Ορισμός του compiler
CC = g++

# Παράμετροι για OpenMP και βελτιστοποίηση O3
CFLAGS = -O3 -fopenmp

# Το όνομα του δικού σου εκτελέσιμου
TARGET = matrix_bash

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(TARGET).cpp -o $(TARGET).exe $(CFLAGS)

clean:
	rm -f $(TARGET).exe