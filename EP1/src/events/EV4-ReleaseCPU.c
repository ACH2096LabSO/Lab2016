//
// Created by brunno on 29/03/16.
//

#include "EV4-ReleaseCPU.h"
#include "../entrada/entrada.h"
#include "../utils/utils.h"
#include "../simulador.h"

void EV4Execute(){

    if (readyProcessLine.first){
        if (readyProcessLine.first->processList){
            if (readyProcessLine.first->processList->type==EXEC_IO){
                transferProcess("EV4", currentTime, &readyProcessLine, &IOProcessLine);
            }
        }
    }
    return;
}