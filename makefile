# the compiler
CC = gcc

# compiler flags
# -g	add debugging info to the executable
# -Wall	turn on (most) compiler warnings
CFLAGS = -g -fmax-errors=5

TARGET = main
OUTFILE = main.o

# data-struct is a separate repo
# clone & adjust paths accordingly
DATA_STRUCTS = ../data-struct/src
SRC = src

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(DATA_STRUCTS)/*.c $(SRC)/*.c $(TARGET).c -o $(OUTFILE)

run:
	./$(OUTFILE)

clean:
	$(RM) $(OUTFILE)
