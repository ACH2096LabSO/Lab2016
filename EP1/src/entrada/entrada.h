#include "../simulador.h"
#include "../messages/messages.h"

#include "../cpu/include/process_struct.h"


#ifndef ENTRADA_H

#define ENTRADA_H

processLine readyProcessLine;         //lista dos processos na fila de "Pronto"
processLine IOProcessLine;            //lista dos processos na fila de "I/O"
processLine waitingProcessLine;       //lista dos processos na fila de "Waiting"
processLine activeProcessLine;        //lista dos processos sendo executados

int mainMemorySize; // Tamanho da memória principal (em número de quadros)
int mainMemoryPageSize;       // Tamanho dos quadros da memória
int cpuTimeSlice;  // CPU time slice para o round robin, se cpuTimeSlice = 0, então o modo deve ser FIFO.
int ioTimeDuration; // Duração das operações de disco
int numProcessos;          // Número de processos

process *setProcess(char* line); //Função para transformar uma linha do arquivo de entrada em uma struct de processo na fila de processos

process* processoAnterior(process *p); //Função que recupera o processo anterior a um processo p


void setParameters(FILE *f); //Função para configurar os parâmetros da simulação vindouros do arquivo de entrada no programa.


void setWaitingList(FILE *f); //Função para criar a waitingProcessLine list de processos, sendo que waitingProcessLine.first é o que chegou primeiro, portanto o que deve sair primeiro.

#endif
