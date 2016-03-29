//
// Created by brunno on 29/03/16.
//


#include "EV2-MemoryAloc.h"
#include "../entrada/entrada.h"
#include "../memory/include/central_memory.h"
#include "../utils/utils.h"
#include "../simulador.h"
#include "../messages/messages.h"

void EV2Execute(){


    while (activeProcessLine.first){
        if (allocate_mem(activeProcessLine.first->memory, activeProcessLine.first->ID) == 1){
            transferProcess("EV2", currentTime, &activeProcessLine, &readyProcessLine);
        }
        else{
            if (framesNeeded(activeProcessLine.first->memory) > mainMemorySize){
                transferProcess("EV2 - Memoria insuficiente", currentTime, &activeProcessLine, &cancelledProcessLine);
            }
            else{

                return;
            }

        }

    }

}