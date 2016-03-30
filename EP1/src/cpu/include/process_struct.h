#include <stdio.h>
#include <stdio.h>
#include <string.h>

#ifndef PROCESS_H
#define PROCESS_H


typedef struct process process;

typedef struct processExecList processExecList;

struct processExecList{
    int ID;
    int type; // 0 seria CPU 1 seria IO, assim sabemos se o processo fica na fila de IO ou passa para a de CPU e vie versa
    processExecList *next;
};



struct process
{
    int ID;           //id do processo
    int arrive_time;  //hora da chegada do processo
    int CPU_burst;    //quantidade de clocks de cpu que o processo consumira
    int CPU_used;     //quantidade de clocks de cpu que o processo ja consumiu
    int memory;       //quantidade de memória alocada para o processo
    int I_O;          //quantidade de requisições de Input e Output
    int I_O_used;

    /* criei a lista de execução do processo para poder dividir a IO igualmente dentro da execução do processo, se nao, nao saberiamos quando o processo deve executar IO e
     * quando deve voltar a fila de execução
     *
     * essa struct cria a lista do que o processo deve fazer e o processo finalizou sua execução quando essa lista está vazia
     * */
    processExecList *processList; //lista de ações que o processo deve executar


    /*resolvi implementar um atributo de tempo de espera (cujo valor padrao eh zero) para representar o tempo que falta para o processo sair do IO.
  	Se seu valor for maior que zero, significa que o processo esta em tempo de espera e nao vai ser executado ate que seu tempo de espera acabe.
  	No round robin, cada clock de cpu reduz o valor desse atributo por 1 se ele for positivo. Dessa forma, o proximo processo a ter seu tempo
  	de espera igual a zero estara pronto para rodar. Os tempos de espera dos processos mais antigos acabarao mais rapidamente que os dos mais
	novo, fazendo com que o grupo de processos em espera se comportem como uma fila */
    int tempoEspera_IO;

    process *next;    //seria interessante implementar como lista ligada, então precisamos de um ponteiro pro próximo processo
};

typedef struct processLine processLine;

struct processLine  // Resolvi criar uma struct para a Fila em si para facilitar o acesso ao último elemento, algo que acredito que será útil para a implementação
{
    char* name;
    process *first;
    process *last;
};

#endif
