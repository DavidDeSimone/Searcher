CC = gcc
CFLAGS = -g -Wall
LFLAGS = -L.

OBJFILES = index.o
OUTPUT = search
all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(LFLAGS) -c search.c -o search.o 
