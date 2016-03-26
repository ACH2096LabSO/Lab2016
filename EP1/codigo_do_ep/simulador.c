#include <stdio.h>
#include "entrada.h"

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

// Seria interessante colocar o código para a execução da simulação aqui
    fclose(f);
    return 0;
}
