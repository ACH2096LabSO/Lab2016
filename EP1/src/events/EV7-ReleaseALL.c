//
// Created by brunno on 29/03/16.
//

#include "EV7-ReleaseAll.h"
#include "../simulador.h"
#include "../entrada/entrada.h"
#include "../memory/include/central_memory.h"

void EV7Execute(){
    if (IOProcessLine.first){
        if (!IOProcessLine.first->processList){
            process *p =IOProcessLine.first ;
            IOProcessLine.first = p->next;
            p->next =NULL;
            free_mem(p->ID);
            finishedJobs ++;
        }
    }

    if (readyProcessLine.first){
        if (!readyProcessLine.first->processList){
            process *p =readyProcessLine.first ;
            readyProcessLine.first = p->next;
            p->next =NULL;
            free_mem(p->ID);
            finishedJobs ++;
        }
    }
    return;
}