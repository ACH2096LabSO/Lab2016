#include "process_struct.h"

#ifndef ENTRADA_H
#define ENTRADA_H

processLine ready;         //lista dos processos na fila de "Pronto"
processLine IO;            //lista dos processos na fila de "I/O"
processLine waiting;       //lista dos processos na fila de "Waiting"
processLine active;        //lista dos processos sendo executados

int mainMemory; // Tamanho da memória principal (em número de quadros)
int size;       // Tamanho dos quadros da memória
int timeSlice;  // CPU time slice para o round robin, se timeSlice = 0, então o modo deve ser FIFO.
int opDuration; // Duração das operações de disco
int n;          // Número de processos

process *setProcess(char* line); //Função para transformar uma linha do arquivo de entrada em uma struct de processo na fila de processos

process* processoAnterior(process *p); //Função que recupera o processo anterior a um processo p


void setParameters(FILE *f); //Função para configurar os parâmetros da simulação vindouros do arquivo de entrada no programa.


void setWaitingList(FILE *f); //Função para criar a waiting list de processos, sendo que waiting.first é o que chegou primeiro, portanto o que deve sair primeiro.

#endif
