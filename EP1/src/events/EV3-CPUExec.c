//
// Created by brunno on 29/03/16.
//

#include "EV3-CPUExec.h"
#include "../entrada/entrada.h"
#include "../utils/utils.h"
#include "../simulador.h"
#include "../messages/messages.h"

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




                //execução de um processo de cpu
                processExecList *e;
                e= readyProcessLine.first->processList;
                readyProcessLine.first->processList = readyProcessLine.first->processList->next;
                readyProcessLine.first->CPU_used++;

                //se for fifo executa até o fim o processo
                printConsumeCPU(p, e);


                if (cpuTimeSlice >0){
                    //se for round robin, checa o cpu_used e caso alcance o cpuTimeSlice o processo é movido para o fim da fila de execução
                    if (readyProcessLine.first->CPU_used >= cpuTimeSlice){
                        transferProcess("EV3 - Round Robin", currentTime, &readyProcessLine, &readyProcessLine);

                    }
                }


            }
        }
    }
    return;
}