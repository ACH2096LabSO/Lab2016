//
// Created by brunno on 29/03/16.
//

#include "messages.h"
#include "../entrada/entrada.h"


void printConfig(){

#ifdef _MESSAGES_
    printf("%s\n", "Config Options");
    printf("%s %i\n", "Tam Memoria:",mainMemorySize);
    printf("%s %i\n", "Tam Quadros de Memoria:",mainMemoryPageSize);
    printf("%s %i\n", "Time Slice CPU:",cpuTimeSlice);
    printf("%s %i\n", "Duracao de IO:",ioTimeDuration);
    printf("%s %i\n", "Num Processsos:",numProcessos);

#endif


}


void printProcess(process* proc, int printExecList){

#ifdef _MESSAGES_
    printf("%s %i %s %i %s %i %s %i %s %i %s %i %s %i\n", "Processo:", proc->ID, "Arrive Time:", proc->arrive_time, "CPU Burst:", proc->CPU_burst,
           "CPU Used:", proc->CPU_used, "Memory:", proc->memory, "Total IO:", proc->I_O, "IO Used:", proc->I_O_used);
    if (printExecList==1){
        processExecList *p = proc->processList;
        while (p!=NULL){
            printf("%s %i %s %i\n", "     Exec:", p->ID, "Type:", p->type);
            p=p->next;
        }
    }

#endif

}

void printProcessList(char* lineName, processLine pline, int printExecList){


#ifdef _MESSAGES_
    printf("%s %s %s\n", "Lista de Processos da lista", lineName, "em ordem");
    if (pline.first==NULL) return;
    process *p = pline.first;
    while (p!=NULL){
        printProcess(p, printExecList);
        p=p->next;
    }
#endif


}


void printMemoryFrameQueue(FREE_FRAMES *freeFrames){

#ifdef _MESSAGES_

    if (freeFrames->head==NULL) return;
    FRAME *f = freeFrames->head;
    printf("%s %i\n", "Imprimindo Lista de Frames - tamanho vazio - ", freeFrames->length);
    while(f!=NULL){
        printf("%s ", "Lista de frames");
        printFrame(f);
        f= f->next;
    }
#endif
}

void printFrame(FRAME *fr){
#ifdef _MESSAGES_
    if (fr!=NULL)
        printf("%s %i %s %i %s %i\n", "Frame:", fr->id, "Adress:", fr->address, "Job:", fr->job_id);
    else
        printf("%s \n", "Frame NULL");
#endif
}


void printMemoryMap(FRAME **memorymap){
#ifdef _MESSAGES_
    int i;

    printf("%s \n", "Imprimindo Mapa da memoria");
    for(i=0;i<mainMemorySize;i++){
        printf("%s %i ", "Local no mapa ", i);
        printFrame(memorymap[i]);
    }

#endif
}

void printOutOfMemory(int available, int required, int jobId){
#ifdef _MESSAGES_

    printf("%s %i %s %i %s %i\n", "Não há memória - Disponível:", available, "Requerida:", required, "Processo:", jobId);
#endif
}

void printFreedTables(int tables)
{
#ifdef _MESSAGES_

    printf("%s %i\n", "Quadros liberados", tables);
#endif
}

void printTransferMessage(char* action, int currenttime, processLine origin, processLine destination, process *p){
#ifdef _MESSAGES_
    printf("%s %i %s %i %s %s %s %s %s %s \n", "Tempo:", currenttime, "Processo:", p->ID, "movido de", origin.name, "para", destination.name, "Motivo:", action);
#endif
}

