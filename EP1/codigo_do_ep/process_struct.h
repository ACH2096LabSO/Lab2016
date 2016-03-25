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
  process *first;
  process *last;
};
