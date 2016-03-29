#include <stdio.h>
#include "include/process_struct.h"

//metodo que zera os tempos de espera um conjunto de processos para que eles sejam executados normalmente durante o round-robin
void zeraTempoDeEspera(process *p){
	process *p2=p;
	while (p2->next != p){
		p2->tempoEspera_IO=0;
		p2=p2->next;
	}
}

//metodo que reduz o tempo de espera de todos os processos na fila de espera
void reduzTempoEspera(process *p){
	process *p2=p;
	while (p2->next != p){
		if(p2->tempoEspera_IO>0){
			p2->tempoEspera_IO--;
			if(p2->tempoEspera_IO==0){
				printf("\n O processo %d saiu da fila de espera \n", p2->ID);
			}
		}
		p2=p2->next;
	}
}

int *definirIntervalosIO (process *p, int numProcessos){
	int* intervalos=(int*)malloc(numProcessos*sizeof(int));
	process *aux=p;
	int i;
	for (i=0; i<numProcessos; i++){
		intervalos[i]=(int)floor(aux->CPU_burst/aux->I_O);
		aux=aux->next;
	}
	return intervalos;
}

//metodo principal do algoritmo round-robin
void roundRobin(process *processo, int timeSlice, int opDuracao, int numProcessos, int duracao_IO) {
    zeraTempoEspera(processo);
	printf ("\n Escalonamento dos processos usando Round Robin (Time Slice = %d) \n", timeSlice );
	int tempo = timeSlice;
	int i = numProcessos;
	int* intervalosIO = definirIntervalosIO (processo, numProcessos);
	int indiceIntervalos=0;
	process *p = processo;
	while (i<0){
		int tempoPassado=0;
		//roda o processo ate que uma das duas condicoes seja atingida:
		//1-o processo terminou de executar
		//2-o processo estourou sua timeSlice
		while (tempoPassado<timeSlice && p->CPU_burst>0 && p->tempoEspera_IO==0) {
			printf ("%s ",p->ID);
			tempoPassado++;
			p->CPU_b--;
			//reduz o tempo de espera de todos os processos cujo tempo de espera eh maior que zero
			reduzTempoEspera(processo);

			if(p->CPU_b==0) {
				//decrementa o contador i se o processo terminou de executar. Quando ele chegar a zero, significa que todos os processos foram executados.
				i--;
			}

			if (p->CPU_b % intervalosIO[indiceIntervalos] == 0) {	//se o processo faz uma chamada IO
				//coloca o processo na fila de espera, ou seja, define um numero de clocks de cpu em que ele nao vai ser executado.
				p->tempoEspera_IO=duracao_IO;
				printf("\n O processo %d entrou da fila de espera \n", p->ID);
			}
		}
		//quando quaisquer das condições supracitadas sejam satisfeitas, o programa passa a execucao para outro processo
		printf ("| ");
		p = p->next;

		if(indiceIntervalos>=numProcessos) {
			indiceIntervalos=0;
		}else{
			indiceIntervalos++;
		}
	}
}

