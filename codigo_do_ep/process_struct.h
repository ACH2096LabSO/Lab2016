#include <stdio.h>
#include <stdio.h>
#include <string.h>

typedef struct process process;

struct process
{
  int ID;           //id do processo
  int arrive_time;  //hora da chegada do processo
  int CPU_b;        //quantidade de clocks de cpu que o processo consumira
  int memory;       //quantidade de memória alocada para o processo
  int I_O;          //quantidade de requisições de Input e Output
  process *next;    //seria interessante implementar como lista ligada, então precisamos de um ponteiro pro próximo processo
};

typedef struct processLine processLine;

struct processLine  // Resolvi criar uma struct para a Fila em si para facilitar o acesso ao último elemento, algo que acredito que será útil para a implementação
{
  process *first;
  process *last;
};