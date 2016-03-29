#include <stdio.h>

#include "simulador.h"

#include "entrada/entrada.h"




void simulate()
{
    int finishedJobs = 0;
    int currentTime = readyProcessLine.first->arrive_time;   //tempo atual de clock

    while(numProcessos > finishedJobs)    //enquanto ainda houver processo em uma das filas
    {
        /*if(activeProcessLine == NULL)
        {
            //alocar CPU
        }

        */
        //possiveis outros eventos vao aqui

        currentTime++;
    }
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

    //simulate();


    fclose(f);


    return 0;

}
