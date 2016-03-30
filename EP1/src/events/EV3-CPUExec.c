//
// Created by brunno on 29/03/16.
//

#include "EV3-CPUExec.h"
#include "../entrada/entrada.h"

void EV3Execute(){

    /* nesse metodo precisa implementar ainda o processo de round robin
     * está simplificado com fifo - pois é mais rapido de implementar
     * mas deve-se ver de novo e conseguir implementar o round robin.
     * para movem um processo para o fim da fila de execução, basta chamar o procedimento
     * transferProcess("EV3 - RoundRobin", currentTime, &readyProcessLine, &readyProcessLine);
     * que ele vai para o fim da fila
     * */


    //se tiver algo a processar
    if (readyProcessLine.first){

        process *p = readyProcessLine.first;


        //execução de CPU
        //aqui deve executar round robin para ver se ele deve ir para o fim da fila ou algo do tipo
        if (readyProcessLine.first->processList){
            if (readyProcessLine.first->processList->type==EXEC_CPU){

                processExecList *e;
                e= readyProcessLine.first->processList;


                readyProcessLine.first->processList = readyProcessLine.first->processList->next;
                printf("%s %i %s %i \n", "EV3 CPU consumido Processo:", p->ID, " ID da lista ", e->ID);
            }
        }
    }
    return;
}