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
    novo->processList = NULL;

    int cpus=0;
    int ios=0;
    int cpuUses=0;
    int execID=0;

    int esperaIO = 0;
    if (novo->I_O >0){
        esperaIO = novo->CPU_burst / novo->I_O;
    }

    while ((novo->CPU_burst>cpus) || (novo->I_O >ios)){


        if (esperaIO==0){
            if (cpus<novo->CPU_burst){
                processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
                novoExec->ID = execID;
                novoExec->type=0;
                novoExec->next=NULL;
                cpus++;
                execID++;
                if (!(novo->processList==NULL)){
                    processExecList *p = novo->processList;
                    while (p->next!=NULL){
                        p=p->next;
                    }
                    p->next = novoExec;
                }
                else{
                    novo->processList = novoExec;
                }
            }
        }
        else{
            while (cpuUses< esperaIO){
                if (cpus<novo->CPU_burst){
                    processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
                    novoExec->ID = execID;
                    novoExec->type=0;
                    novoExec->next=NULL;
                    cpus++;
                    execID++;
                    if (!(novo->processList==NULL)){
                        processExecList *p = novo->processList;
                        while (p->next!=NULL){
                            p=p->next;
                        }
                        p->next = novoExec;
                    }
                    else{
                        novo->processList = novoExec;
                    }
                }
                cpuUses++;
            }
        }



        cpuUses=0;
        if (ios<novo->I_O){
            processExecList  *novoExec = (processExecList*) malloc(sizeof(processExecList));
            novoExec->ID = execID;
            novoExec->type=1;
            novoExec->next=NULL;
            ios++;
            execID++;
            if (!(novo->processList==NULL)){
                processExecList *p = novo->processList;
                while (p->next!=NULL){
                    p=p->next;
                }
                p->next = novoExec;
            }
            else{
                novo->processList = novoExec;
            }
        }




    }

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
