CC = gcc
CFLAGS = -c -Wall
SRCPATH = src
EXEC = bin/simulador
OBJECTS = simulador.o entrada.o

all: link

link: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

simulador.o: entrada.o
	$(CC) $(CFLAGS) $(SRCPATH)/simulador.c

entrada.o:
	$(CC) $(CFLAGS) $(SRCPATH)/entrada.c

clean:
	rm -rf *.o
