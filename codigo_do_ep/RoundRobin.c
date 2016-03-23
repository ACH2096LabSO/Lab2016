#include <stdio.h>
#include "process_struct.h"

void roundRobin(FILE *saida, process processo, int timeSlice, int opDuracao, int numProcessos) {
	fprintf ( saida, "\n Escalonamento dos processos usando Round Robin (Time Slice = %d) \n", timeSlice );
	int tempo = timeSlice;
	int i = numProcessos;
	process p = processo;
	while (i<0){
		int tempoPassado=0;
		//roda o processo ate que uma das duas condicoes seja atingida:
		//1-o processo terminou de executar
		//2-o processo estourou sua timeSlice
		while (tempoPassado<timeSlice && p->CPU_b>0) {
			fprintf (saida, "%s ",p->ID);
			tempoPassado++;
			p->CPU_b--;
		}
		//quando quaisquer das condições supracitadas sejam satisfeitas, o programa passa a execucao para outro processo
		fprintf (saida, "| ");
		p = p->next;		
		//decrementa o contador i. Quando ele chegar a zero, é sinal de que todos os processos foram executados.
		i--;	
	}
}