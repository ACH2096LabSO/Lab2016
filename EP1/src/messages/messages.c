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


void printProcess(process* proc){

#ifdef _MESSAGES_
        printf("%s %i %s %i %s %i %s %i %s %i %s %i %s %i\n", "Processo:", proc->ID, "Arrive Time:", proc->arrive_time, "CPU Burst:", proc->CPU_burst,
               "CPU Used:", proc->CPU_used, "Memory:", proc->memory, "Total IO:", proc->I_O, "IO Used:", proc->I_O_used);
#endif

}

void printProcessList(char* lineName, processLine pline){


#ifdef _MESSAGES_
    printf("%s\n", "Lista de Processos em ordem");
    process *p = pline.first;
    while (p!=NULL){
        printProcess(p);
        p=p->next;
    }
#endif



}

