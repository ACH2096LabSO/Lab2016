//QUALQUER D�VIDA OU SUGEST�O COMENTEM NO C�DIGO
//N�o fiz muitos testes mas n�o deve dar maiores problemas


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "../messages/messages.h"



process *setProcess(char* line)
{
    char *aux;
    process *novo = (process*) malloc(sizeof(process));

    aux = strtok(line, ";");
    novo->ID = atoi(aux);
    aux = strtok(NULL, ";");
    novo->arrive_time = atoi(aux);
    aux = strtok(NULL, ";");
    novo->CPU_burst = atoi(aux);
    aux = strtok(NULL, ";");
    novo->CPU_used = 0;
    novo->memory = atoi(aux);
    aux = strtok(NULL, ";");
    novo->I_O = atoi(aux);
    novo->I_O_used=0;
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
    int res = fscanf(f, "%s", line);

    if (res>0){


        aux = strtok(line, ";");
        mainMemorySize = atoi(aux);
        aux = strtok(NULL, ";");
        mainMemoryPageSize = atoi(aux);
        aux = strtok(NULL, ";");
        cpuTimeSlice = atoi(aux);
        aux = strtok(NULL, ";");
        ioTimeDuration = atoi(aux);
        aux = strtok(NULL, ";");
        numProcessos = atoi(aux);


        printConfig();
    }


    return;
}

void setWaitingList(FILE *f) //Criar a waitingList por ordem de chegada
{
    char line[100];
    process *aux, *aux2, *ant;
    int i;

    int res = fscanf(f, "%s", line);
    if (res>0) {

        aux = setProcess(line);
        waitingProcessLine.first = aux;
        waitingProcessLine.last = aux;
        readyProcessLine.first=NULL;
        readyProcessLine.last=NULL;
        IOProcessLine.first=NULL;
        IOProcessLine.last=NULL;
        activeProcessLine.first=NULL;
        activeProcessLine.last=NULL;

        for (i = 1; i < numProcessos; i++)
        {
            res = fscanf(f, "%s", line);
            if (res>0){
                aux = setProcess(line);
                //Faz a insercao ordenada dos processos que s?o lidos
                //Insercao na cabeca da fila
                if (aux->arrive_time <= waitingProcessLine.first->arrive_time) {
                    aux->next = waitingProcessLine.first;
                    waitingProcessLine.first = aux;
                }
                else {
                    ant = waitingProcessLine.first;
                    aux2 = waitingProcessLine.first;
                    //Percorre a fila de espera at? achar a posi??o do novo processo pelo seu Arrive_time
                    while (aux2->next != NULL && aux->arrive_time > aux2->arrive_time) {
                        ant = aux2;
                        aux2 = aux2->next;
                    }
                    //Novo processo tem o tempo de chegada menor que o processo atual, ent?o vira o proximo do anterior
                    if (aux->arrive_time < aux2->arrive_time) {
                        ant->next = aux;
                        aux->next = aux2;
                    }
                        //Novo processo tem o tempo de chegada maior que o processo atual, ent?o vira o ultimo da fila
                    else {
                        aux->next = aux2->next;
                        aux2->next = aux;
                        waitingProcessLine.last = aux;
                    }
                }
            }
        }
    }

    printProcessList("Waiting List", waitingProcessLine);

}
