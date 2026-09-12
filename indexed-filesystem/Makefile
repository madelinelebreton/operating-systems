# Makefile for indexed file system

# compiler
CC = gcc

# flags
CFLAGS = -Wall -Wextra -std=c11

# target executable
TARGET = fs_sim

# default rule
all: $(TARGET)

# link object files
$(TARGET): main.o fs_indexed.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o fs_indexed.o -lm


# compile main.c
main.o: main.c fs_indexed.h
	$(CC) $(CFLAGS) -c main.c

# compile fs_indexed.c
fs_indexed.o: fs_indexed.c fs_indexed.h
	$(CC) $(CFLAGS) -c fs_indexed.c

# run the program
run: $(TARGET)
	./$(TARGET)

# clean build files
clean:
	rm -f *.o $(TARGET)

