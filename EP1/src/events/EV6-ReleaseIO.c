//
// Created by brunno on 29/03/16.
//

#include "EV6-ReleaseIO.h"
#include "../entrada/entrada.h"
#include "../utils/utils.h"
#include "../simulador.h"

void EV6Execute(){

    if (IOProcessLine.first){
        if (IOProcessLine.first->processList){
            if (IOProcessLine.first->processList->type==EXEC_CPU){
                transferProcess("EV4", currentTime, &IOProcessLine, &readyProcessLine);
            }
        }
    }
    return;
}