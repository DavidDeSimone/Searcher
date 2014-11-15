CC = gcc
CFLAGS = -g -Wall
LFLAGS = -L.

OBJFILES = index.o search.o liblist.o parser.o
OUTPUT = search
SUBAPPS = indexer
all: $(OUTPUT) $(SUBAPPS)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LFLAGS) -o $(OUTPUT) 

search.o: search.c
	$(CC) $(CFLAGS) $(LFLAGS) -c search.c -o search.o 

indexer: index_main.o liblist.o
	$(CC) $(CFLAGS) $(LFLAGS) index_main.o liblist.o -o indexer

liblist.o: Index/listcoll.c
	$(CC) $(CFLAGS) $(LFLAGS) -c Index/listcoll.c -o liblist.o

index.o: Index/index.c
	$(CC) $(CFLAGS) $(LFLAGS) -c Index/index.c -o index.o

index_main.o: Index/index_main.c
	$(CC) $(CFLAGS) $(LFLAGS) -c Index/index_main.c -o index_main.o

parser.o: parser.c
	$(CC) $(CFLAGS) $(LFLAGS) -c parser.c -o parser.o




clean:
	rm ./*.o ./search ./indexer

