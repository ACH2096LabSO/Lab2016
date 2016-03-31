# Relatório de Exercício-Programa 1


### Memória

Para implementação da memória, optou-se por criar estruturas para definir os quadros da memória (lista ligada), uma estrutura de fila *FIFO* simples para a *Fila da CM*, uma tabela para mapear os quadros das memórias físicas e lógicas; e funções para manipular essas estruturas.

#### Estruturas

```
typedef struct frame FRAME;
typedef struct frames FREE_FRAMES;

struct frame {
    int id;
    int address;
    int job_id;
    FRAME *next;
};

struct frames {
    FRAME *head;
    FRAME *tail;
    int length;
};

FRAME **MEMORY_MAP_TABLE;
```

As estruturas acima são a base do módulo de memória.



#### Funções

##### Inicialização de Memória
`int init_mem(int num_frames, int frame_size);`

Inicializa a memória, a tabela da memória e a fila da memória, com o intuito de ter o módulo preparado para receber alocações dos processos simulados. O módulo deve ser iniciado antes de funcionar, para que todas as estruturas sejam devidamente inicializadas.


##### Inicialização de Fila
`int init_queue(FREE_FRAMES **queue, int num_frames, int frame_size);`

Responsável por inicializar a fila da memória, que receberá processos caso não haja espaço suficiente para alocá-los. É chamada por `int init_mem(int num_frames, int frame_size)`.


##### Inicialização de Tabela de Memória
`int init_map(FRAME ***map, int num_frames);`

Utiliza-se essa função para inicializar a tabela da memória, que mapeia os endereços físicos para os endereços lógicos, permitindo o uso de páginas intercaladas na memória física. Chamada por `int init_mem(int num_frames, int frame_size)`.


##### Alocação de Memória
`int allocate_mem(int size, int job_id);`

Método utilizado para alocar algum processo na memória. Esse método verifica se o processo pode ser alocado na memória de acordo com seu `int size` e, em caso afirmativo, as estruturas `FRAME` receberam em seu atributo `int id` o valor do `int job_id` passado como parâmetro nessa função.  Caso não haja espaço suficiente para alocar o processo, este será enviado para  a fila da memória, afim de esperar que haja espaço suficiente para ser alocado.

##### Liberação de Memória
`void free_mem(int job_id);`

Função para limpar a memória ocupada por determinado processo. Essa função buscará o processo com identificação `int job_id` e o removerá da memória, liberando espaço para outros processos.


