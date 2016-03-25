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
enum TYPE
{
    PHYSICAL,
    LOGICAL
}

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

 int init_memory(int size, int num_page, int page_size,
                 TYPE type)

 Inicializa a memoria simulada. A depender da flag 'type',
 a memoria sera fisica ou logica

 @param
 int size      - Tamanho da memoria
 int num_page  - Numero de paginas
 int page_size - Tamanho das paginas
 TYPE type     - Tipo da memoria

 @return
 0  : Memoria inicializada com sucesso
 1  : Tamanho de paginas nao alcancado - pouca memoria
 -1 : Tamanho de pagina maior que tamanho da memoria ERRO
 -2 : Tamanho de pagina fisica e logica diferentes ERRO

**********************************************************/

int init_mem(int size, int num_page, int page_size, TYPE type);

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
