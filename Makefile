CC = gcc
CFLAGS = -g -Wall
LFLAGS = -L.

OBJFILES = index.o search.o liblist.o
OUTPUT = search
all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LFLAGS) -o $(OUTPUT) 

search.o: search.c
	$(CC) $(CFLAGS) $(LFLAGS) -c search.c -o search.o 

liblist.o: Index/listcoll.c
	$(CC) $(CFLAGS) $(LFLAGS) -c Index/listcoll.c -o liblist.o

index.o: Index/index.c
	$(CC) $(CFLAGS) $(LFLAGS) -c Index/index.c -o index.o


clean:
	rm ./*.o ./search

