#include <stdio.h>
#include "entrada.h"

void simulate()
{
    int finishedJobs = 0;
    process* assignedJob = NULL;    //job atualmente assinalado à CPU
    int currentTime = waiting.first->arrive_time;   //tempo atual de clock

    while(n > finishedJobs)    //enquanto ainda houver processo em uma das filas
    {
        if(assignedJob == NULL)
        {
            //evento 1
        }

        //possiveis outros eventos vao aqui

        currentTime++;
    }
}

int main(int argc, char *argv[]) // main para inicializar o programa. qualquer dúvida comentar no código
{
    FILE *f = NULL;
    int i;


    f = fopen(argv[1], "r");

    if(f == NULL)
    {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        return 0;
    }

    setParameters(f);

    setWaitingList(f);

    simulate();

    fclose(f);
    return 0;
}
