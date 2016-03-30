//QUALQUER DUVIDA OU SUGESTAO COMENTEM NO CODIGO
//Nao fiz muitos testes mas nao deve dar maiores problemas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "../messages/messages.h"


void addProcessLine(process *processo){

    int cpus=0;
    int ios=0;
    int cpuUses=0;
    int execID=0;

    // Tempo de processamento entre atividades de IO
    int esperaIO = 0;
    if (processo->I_O >0){
        esperaIO = processo->CPU_burst / processo->I_O;
    }

    while ((processo->CPU_burst>cpus) || (processo->I_O >ios)){
        /**
         * Caso o processo não realize IO, apenas preencher a lista de
         * execucao. Cada tempo de clock eh representado por uma entrada.
         */
        if (esperaIO==0){
            if (cpus<processo->CPU_burst){
                processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
                novoExec->ID = execID;
                novoExec->type=EXEC_CPU;
                novoExec->next=NULL;
                cpus++;
                execID++;
                if (!(processo->processList==NULL)){
                    processExecList *p = processo->processList;
                    while (p->next!=NULL){
                        p=p->next;
                    }
                    p->next = novoExec;
                }
                else{
                    processo->processList = novoExec;
                }
            }
        }
        else{
            while (cpuUses< esperaIO){
                /**
                 * Insere tempos de clocks que precedem uma atividade de IO
                 * */
                if (cpus<processo->CPU_burst){
                    processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
                    novoExec->ID = execID;
                    novoExec->type=EXEC_CPU;
                    novoExec->next=NULL;
                    cpus++;
                    execID++;
                    if (!(processo->processList==NULL)){
                        processExecList *p = processo->processList;
                        while (p->next!=NULL){
                            p=p->next;
                        }
                        p->next = novoExec;
                    }
                    else{
                        processo->processList = novoExec;
                    }
                }
                cpuUses++;
            }
        }
        cpuUses=0;

        /**
         * Insere tempos de clock correspondentes a uma atividade de IO
         * */
        if (ios<processo->I_O){

            int tempos=0;
            while (tempos<ioTimeDuration){
                processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
                novoExec->ID = execID;
                novoExec->type=EXEC_IO;
                novoExec->next=NULL;
                if (!(processo->processList==NULL)){
                    processExecList *p = processo->processList;
                    while (p->next!=NULL){
                        p=p->next;
                    }
                    p->next = novoExec;
                }
                else{
                    processo->processList = novoExec;
                }
                tempos++;
            }
            ios++;
            execID++;

        }
    }
}


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
    novo->processList = NULL;
    addProcessLine( novo);


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
        waitingProcessLine.name="Entrada";
        waitingProcessLine.first = aux;
        waitingProcessLine.last = aux;
        readyProcessLine.name="Prontos";
        readyProcessLine.first=NULL;
        readyProcessLine.last=NULL;
        IOProcessLine.name="IO";
        IOProcessLine.first=NULL;
        IOProcessLine.last=NULL;
        activeProcessLine.name="Ativos";
        activeProcessLine.first=NULL;
        activeProcessLine.last=NULL;
        cancelledProcessLine.name="Cancelados";
        cancelledProcessLine.first=NULL;
        cancelledProcessLine.last=NULL;

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

    printProcessList("Waiting List", waitingProcessLine,1);

}
