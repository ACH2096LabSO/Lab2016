#include <stdio.h>

#include "simulador.h"
#include "entrada/entrada.h"
#include "messages/messages.h"

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
    int finishedJobs = 0;

    init_mem(mainMemorySize, mainMemoryPageSize);
    //testMem();

    if (waitingProcessLine.first==NULL) {
        printf("%s\n", "Nenhum processo na fila");
        return 0;
    }

    int currentTime = waitingProcessLine.first->arrive_time;   //tempo atual de clock


    while(numProcessos > finishedJobs)    //enquanto ainda houver processo em uma das filas
    {

        /*if(activeProcessLine!=NULL)
        {
            //alocar CPU
        }*/


        //possiveis outros eventos vao aqui

        currentTime++;

        if (currentTime==500) break;
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


    return resultSimulate;

}
