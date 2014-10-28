CC = gcc
CLFAGS = -g -Wall
LFLAGS = -L.
IFLAGS = -I.

OUTPUT = index
OBJFILES = liblist.o index.o
all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LFLAGS) -o $(OUTPUT) $(IFLAGS)

liblist.o: listcoll.c
	$(CC) $(CFLAGS) -c listcoll.c -o liblist.o $(IFLAGS)

index.o: index.c
	$(CC) $(CFLAGS) -c index.c -o index.o $(IFLAGS)




clean:
	rm *.o $(OUTPUT)
