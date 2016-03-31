CC = gcc
CFLAGS = -c -Wall
SRCPATH = src
EXEC = bin/simulador
OBJECTS = simulador.o entrada.o utils.o messages.o central_memory.o EV1-NewJobs.o EV2-MemoryAloc.o EV3-CPUExec.o EV4-ReleaseCPU.o EV5-IOExecution.o EV6-ReleaseIO.o EV7-ReleaseALL.o

all: link

link: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

simulador.o: entrada.o utils.o messages.o EV1-NewJobs.o EV2-MemoryAloc.o EV3-CPUExec.o EV4-ReleaseCPU.o EV5-IOExecution.o EV6-ReleaseIO.o EV7-ReleaseALL.o
	$(CC) $(CFLAGS) $(SRCPATH)/simulador.c

entrada.o: messages.o
	$(CC) $(CFLAGS) $(SRCPATH)/entrada/entrada.c

messages.o:
	$(CC) $(CFLAGS) $(SRCPATH)/messages/messages.c

utils.o: messages.o
	$(CC) $(CFLAGS) $(SRCPATH)/utils/utils.c

central_memory.o: messages.o
	$(CC) $(CFLAGS) $(SRCPATH)/memory/central_memory.c

EV1-NewJobs.o: utils.o messages.o
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV1-NewJobs.c

EV2-MemoryAloc.o: utils.o messages.o central_memory.o  
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV2-MemoryAloc.c

EV3-CPUExec.o:
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV3-CPUExec.c

EV4-ReleaseCPU.o: utils.o
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV4-ReleaseCPU.c

EV5-IOExecution.o:
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV5-IOExecution.c

EV6-ReleaseIO.o: utils.o
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV6-ReleaseIO.c

EV7-ReleaseALL.o: central_memory.o
	$(CC) $(CFLAGS) $(SRCPATH)/events/EV7-ReleaseALL.c

clean:
	rm -rf *.o
