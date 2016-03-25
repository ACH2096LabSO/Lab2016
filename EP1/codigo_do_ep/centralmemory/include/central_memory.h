/**********************************************************

 Header da memoria central CM

 Esse arquivo contem as funcoes e estruturas referentes
 a memoria central do simulador BASYS desenvolvido.

 Quem mexeu:

  - Gustavo Kishima




                             Data de criacao: 24 Mar 2016

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

**********************************************************/

int init_physical_mem(int size, int num_page, int page_size, TYPE type);

/**********************************************************

 int allocate_mem(int size, int job_id);

 Aloca a memoria para algum processo.

 @param
 int size   - Tamanho da memoria
 int job_id - Identificacao do processo

 @return
 0  : memoria alocada com sucesso
 1  : Memoria nao pode ser alocada - espaco insuficiente
 2  : Memoria nao pode ser alocada - espaco contiguo
      insuficiente
 -1 : Memoria nao pode ser alocada - ERRO

***********************************************************/

int allocate_mem(int size, int job_id);
