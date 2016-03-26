//QUALQUER DÚVIDA OU SUGESTÃO COMENTEM NO CÓDIGO
//Não fiz muitos testes mas não deve dar maiores problemas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "process_struct.h"

process *setProcess(char* line)
{
    char *aux;
    process *new = malloc(sizeof(process));

    aux = strtok(line, ";");
    new->ID = atoi(aux);
    aux = strtok(NULL, ";");
    new->arrive_time = atoi(aux);
    aux = strtok(NULL, ";");
    new->CPU_b = atoi(aux);
    aux = strtok(NULL, ";");
    new->memory = atoi(aux);
    aux = strtok(NULL, ";");
    new->I_O = atoi(aux);

    return new;
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

void setWaitingList(FILE *f)
{
    char line[100];
    process* aux;
    int i;

    fscanf(f, "%s", line);
    aux = setProcess(line);
    waiting.first = aux;
    waiting.last = aux;


    for(i = 1; i < n; i++)
    {
        fscanf(f, "%s", line);
        aux = setProcess(line);
        waiting.last->next = aux;
        waiting.last = aux;
    }
}
