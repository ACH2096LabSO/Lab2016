//QUALQUER D√öVIDA OU SUGEST√ÉO COMENTEM NO C√ìDIGO
//N√£o fiz muitos testes mas n√£o deve dar maiores problemas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "cpu/include/process_struct.h"

process *setProcess(char* line)
{
	char *aux;
	process *novo = (process*) malloc(sizeof(process));

	aux = strtok(line, ";");
	novo->ID = atoi(aux);
	aux = strtok(NULL, ";");
	novo->arrive_time = atoi(aux);
	aux = strtok(NULL, ";");
	novo->CPU_b = atoi(aux);
	aux = strtok(NULL, ";");
	novo->memory = atoi(aux);
	aux = strtok(NULL, ";");
	novo->I_O = atoi(aux);
	novo->next = NULL;

	return novo;
}

process* processoAnterior(process *p)
{
    process *aux = p;
    while(aux->next!=p){
        aux=aux->next;
    }
    return aux;    
}

void setParameters(FILE *f)
{
    char *aux;
    char line[100];
    fscanf(f, "%s", line);

    aux = strtok(line, ";");
    mainMemory = atoi(aux);
    aux = strtok(NULL, ";");
    size = atoi(aux);
    aux = strtok(NULL, ";");
    timeSlice = atoi(aux);
    aux = strtok(NULL, ";");
    opDuration = atoi(aux);
    aux = strtok(NULL, ";");
    n = atoi(aux);

    return;
}

void setWaitingList(FILE *f) //Criar a waitingList por ordem de chegada
{
	char line[100];
	process *aux, *aux2, *ant;
	int i;

	fscanf(f, "%s", line);
	aux = setProcess(line);
	waiting.first = aux;
	waiting.last = aux;


	for (i = 1; i < n; i++)
	{
		fscanf(f, "%s", line);
		aux = setProcess(line);
		//Faz a inserÁ„o ordenada dos processos que s„o lidos
		//InserÁ„o na cabeÁa da fila
		if (aux->arrive_time <= waiting.first->arrive_time) {
			aux->next = waiting.first;
			waiting.first = aux;
		}
		else {
			ant = waiting.first;
			aux2 = waiting.first;
			//Percorre a fila de espera atÈ achar a posiÁ„o do novo processo pelo seu Arrive_time
			while (aux2->next != NULL && aux->arrive_time > aux2->arrive_time) {
				ant = aux2;
				aux2 = aux2->next;
			}
			//Novo processo tem o tempo de chegada menor que o processo atual, ent„o vira o proximo do anterior
			if (aux->arrive_time < aux2->arrive_time) {
				ant->next = aux;
				aux->next = aux2;
			}
			//Novo processo tem o tempo de chegada maior que o processo atual, ent„o vira o ultimo da fila
			else {
				aux->next = aux2->next;
				aux2->next = aux;
				waiting.last = aux;
			}
		}
	}
}
