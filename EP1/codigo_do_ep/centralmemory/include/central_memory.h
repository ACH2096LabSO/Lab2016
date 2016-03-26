/**********************************************************

 Header da memoria central CM

 Esse arquivo contem as funcoes e estruturas referentes
 a memoria central do simulador BASYS desenvolvido.

 Quem mexeu:

  - Gustavo Kishima
  - Leonardo Rocha


                             Data de criacao: 24 Mar 2016
                           Data de alteracao: 25 Mar 2016

**********************************************************/


/**********************************************************

 Tipo para definir se a memoria fisica ou logica sera
 inicializada

**********************************************************/

typedef enum type TYPE;

enum type
{
    PHYSICAL,
    LOGICAL
};

/**********************************************************

 Estrutura da fila de molduras livres na memoria

***********************************************************/

typedef struct frame FRAME;
typedef struct frames FREE_FRAMES;

struct frame {
    int frame_id;
    FRAME *next;
};

struct frames {
    FRAME *head;
    FRAME *tail;
    int length;
};

/**********************************************************

 int *PHYSICAL_MEMORY
 int *LOGICAL_MEMORY

 Ponteiros para as estruturas relativas as memorias
 fisica e logica do simulador

**********************************************************/

int *PHYSICAL_MEMORY;
int *LOGICAL_MEMORY;

/**********************************************************
 int **MEMORY_MAP_TABLE;

 Tabela do mapeamento de memoria logica para memoria
 fisica

**********************************************************/

int **MEMORY_MAP_TABLE;

/**********************************************************

 FREE_FRAMES *FREE_FRAMES_QUEUE;

 Fila de molduras disponiveis em memoria fisica

***********************************************************/

FREE_FRAMES *FREE_FRAMES_QUEUE;

/**********************************************************

 int init_memory(int num_frames, int frame_size);

 Inicializa a memoria simulada. A depender da flag 'type',
 a memoria sera fisica ou logica

 @param
 int num_frames  - Tamanho, em quadros, da memoria
 int frame_size  - Numero de paginas por quadro

 @return
  1 : Memoria inicializada com sucesso
  0 : Memoria ja inicializada
 -1 : Espaco insuficiente (simulador) - ERRO
 -2 : Parametros invalidos

**********************************************************/

int init_mem(int num_frames, int frame_size);

/**********************************************************

 int allocate_mem(int size, int job_id);

 Aloca a memoria para algum processo.

 @param
 int size   - Tamanho da memoria
 int job_id - Identificacao do processo

 @return
  0 : memoria alocada com sucesso
  1 : Memoria nao pode ser alocada - espaco insuficiente
 -1 : Memoria nao pode ser alocada - ERRO

***********************************************************/

int allocate_mem(int size, int job_id);

/**********************************************************

 void free_mem(int job_id);

 Libera memoria alocada para determinado processo.

 @param
 int job_id - Identificacao do processo

***********************************************************/

void free_mem(int job_id);
