//QUALQUER DÚVIDA OU SUGESTÃO COMENTEM NO CÓDIGO
//Não fiz muitos testes mas não deve dar maiores problemas

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "process_struct.h"

processLine ready;         //lista dos processos na fila de "Pronto"
processLine IO;            //lista dos processos na fila de "I/O"
processLine waiting;       //lista dos processos na fila de "Waiting"
processLine active;        //lista dos processos sendo executados

int mainMemory; // Tamanho da memória principal (em número de quadros)
int size;       // Tamanho dos quadros da memória
int timeSlice;  // CPU time slice para o round robin, se timeSlice = 0, então o modo deve ser FIFO.
int opDuration; // Duração das operações de disco
int n;          // Número de processos


process *setProcess(char* line) //Função para transformar uma linha do arquivo de entrada em uma struct de processo na fila de processos
{
    char *aux;
    process *new = malloc(sizeof(process));

    aux = strtok(line, ";");
    new->ID = atoi(aux);
    aux = strtok(NULL, ";");
    new->arrive_time = atoi(aux);
    aux = strtok(NULL, ";");
    new->CPU_b = atoi(aux);
    aux = strtok(NULL, ";");
    new->memory = atoi(aux);
    aux = strtok(NULL, ";");
    new->I_O = atoi(aux);

    return new;
}

<<<<<<< HEAD
process processoAnterior(process p) //Função que recupera o processo anterior a um processo p
{
    process aux=p;
    while(aux->next!=p){
        aux=aux->next;
    }
    return aux;    
}

=======
>>>>>>> b93ba7a56373d6d4c373b97117c4d684ff3edc14

void setParameters(FILE *f)     //Função para configurar os parâmetros da simulação vindouros do arquivo de entrada no programa.
{
    char *aux;
    char line[100];
    fscanf(f, "%s", line);

    aux = strtok(line, ";");
    mainMemory = atoi(aux);
    aux = strtok(NULL, ";");
    size = atoi(aux);
    aux = strtok(NULL, ";");
    timeSlice = atoi(aux);
    aux = strtok(NULL, ";");
    opDuration = atoi(aux);
    aux = strtok(NULL, ";");
    n = atoi(aux);

    return;
}


void setWaitingList(FILE *f) //Função para criar a waiting list de processos, sendo que waiting.first é o que chegou primeiro, portanto o que deve sair primeiro.
{
    char line[100];
    process* aux;
    int i;

    fscanf(f, "%s", line);
    aux = setProcess(line);
    waiting.first = aux;
    waiting.last = aux;


    for(i = 1; i < n; i++)
    {
        fscanf(f, "%s", line);
        aux = setProcess(line);
        waiting.last->next = aux;
        waiting.last = aux;
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

    fclose(f);
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> b93ba7a56373d6d4c373b97117c4d684ff3edc14
