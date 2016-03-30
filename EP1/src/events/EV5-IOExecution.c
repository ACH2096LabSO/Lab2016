//
// Created by brunno on 29/03/16.
//

#include "EV5-IOExecution.h"
#include "../entrada/entrada.h"

void EV5Execute(){



    //se tiver algo a processar
    if (IOProcessLine.first){

        //execução de IO
        // io está em FIFO e um processo fica executando io até ele terminar essa io
        if(IOProcessLine.first->processList){
            if (IOProcessLine.first->processList->type==EXEC_IO){
                IOProcessLine.first->processList = IOProcessLine.first->processList->next;
            }
        }
    }


    return;
}