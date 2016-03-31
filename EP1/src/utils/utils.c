//
// Created by brunno on 29/03/16.
//


#include "utils.h"
#include "../messages/messages.h"


void transferProcess(char* action, int currentTime, processLine *origin, processLine *destination){

    if (currentTime==19)
        printf("%s", "erro aqui\n");

    process *p;
    p = origin->first;
    origin->first=p->next;
    if (origin->first==NULL)
        origin->last=NULL;


    p->next = NULL;

    if (destination->last){
        destination->last->next=p;
        destination->last=p;
    }
    else
    {
        destination->first=p;
        destination->last=p;
    }

    p->CPU_used=0;


    printTransferMessage(action, currentTime, *origin, *destination, p);

}


