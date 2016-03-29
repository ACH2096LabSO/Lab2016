//
// Created by brunno on 29/03/16.
//

#include "EV1-NewJobs.h"
#include "../entrada/entrada.h"
#include "../utils/utils.h"
#include "../simulador.h"
#include "../messages/messages.h"

void EV1Execute()
{
    while (waitingProcessLine.first){
        if (waitingProcessLine.first->arrive_time<=currentTime){
            transferProcess("EV1", currentTime, &waitingProcessLine, &activeProcessLine);
            //printProcessList("Active List", activeProcessLine);

        }
        else
            return;
    }
}