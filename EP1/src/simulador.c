#include <stdio.h>
#include <unistd.h>

#include "simulador.h"
#include "entrada/entrada.h"
#include "messages/messages.h"
#include "utils/utils.h"
#include "events/EV1-NewJobs.h"
#include "events/EV2-MemoryAloc.h"
#include "events/EV3-CPUExec.h"
#include "events/EV4-ReleaseCPU.h"
#include "events/EV5-IOExecution.h"
#include "events/EV6-ReleaseIO.h"
#include "events/EV7-ReleaseAll.h"


void testMem(){

    //printMemoryFrameQueue(FREE_FRAMES_QUEUE);
    //printMemoryMap(MEMORY_MAP_TABLE);
    //allocate_mem(45, 1);
    //allocate_mem(138, 2);
    allocate_mem(301, 1);
    allocate_mem(5, 2);
    allocate_mem(12, 3);

    free_mem(2);
    allocate_mem(26, 4);
    free_mem(3);
    allocate_mem(648, 5);
    allocate_mem(12, 6);
    allocate_mem(3, 7);
    free_mem(1);
    allocate_mem(73, 8);
    free_mem(6);
    free_mem(7);
    //printMemoryFrameQueue(FREE_FRAMES_QUEUE);
    //printMemoryMap(MEMORY_MAP_TABLE);
    free_mem(8);
    free_mem(5);
    free_mem(4);
    printMemoryFrameQueue(FREE_FRAMES_QUEUE);
    printMemoryMap(MEMORY_MAP_TABLE);


}


int simulate()
{
    finishedJobs = 0;
    init_mem(mainMemorySize, mainMemoryPageSize);
    //testMem();

    if (waitingProcessLine.first==NULL) {
        printf("%s\n", "Nenhum processo na fila");
        return 0;
    }

    currentTime = waitingProcessLine.first->arrive_time;   //tempo atual de clock

    while(numProcessos  > finishedJobs)    //enquanto ainda houver processo em uma das filas
    {



        EV1Execute();
        EV2Execute();
        EV3Execute();
        EV4Execute();
        EV5Execute();
        EV6Execute();
        EV7Execute();


        currentTime++;

        if (currentTime==10000){
            printMemoryMap(MEMORY_MAP_TABLE);
            printProcessList("espera", waitingProcessLine, 0);
            printProcessList("Ativos", readyProcessLine, 1);
            printProcessList("io ", IOProcessLine, 1);
            sleep(3);
            return 0;
        }

    }
    return 0;
}

int main(int argc, char *argv[]) // main para inicializar o programa. qualquer dúvida comentar no código
{
    FILE *f = NULL;


    f = fopen(argv[1], "r");

    if(f == NULL)
    {
        printf("%s\n","Não foi possível abrir o arquivo de entrada.");
        return 0;
    }

    setParameters(f);
    setWaitingList(f);
    fclose(f);

    int resultSimulate = simulate();

    sleep(3);


    return resultSimulate;

}
