# Sistema de Simulação BASYS

### Composição
* **CPU** (Processador central)
* **CM** (Memória Central)
* **DISK** (Cabeçote de disco)

### Processamento

1. Um _processo_ chega ao sistema;
2. Memória Central (**CM**)  é requerida para o _processo_. Se a memória não está disponível, _processo_ entra numa fila;
3. O processador central (**CPU**) é requerido. Se estiver livre, o _processo_ é entregue para ele, que o executa até que uma _I/O_ (entrada e saída) seja encontrada ou que a execução seja finalizada. Se o **CPU** estiver ocupado, o _processo_ entra numa fila;
4. Quando um _processo_ requer uma _I/O_, ele libera o **CPU**. (Se há outro _processo_ esperando na fila do **CPU**, o _processo_ é agora incumbido para o **CPU**. Se o disco (**DISK**) estiver livre, ele recebe a tarefa de processar a _I/O_ do _processo_. Se o **DISK** estiver ocupado, a requisição do _processo_ entra numa fila;
5. Ao completar uma requisição de _I/O_, o **DISK** é liberado e o **CPU** é requisitado outra vez. Quando o **DISK** é liberado, sua fila é verificada. caso haja outro _processo_ lá com requisição de _I/O_, ela é assinalada ao **DISK**;
6. Ao completar a execução, o _processo_ libera o **CPU** e o espaço que o _processo_ ocupava na **CM** é liberado (a fila da **CM** é checada para verificar se há um processo cujo tamanho possa ser alocado a **CM**, e a fila do **CPU** é verificada para determinar se há um _processo_ esperando para ser assinalado ao **CPU**;
7. O _processo_ deixa o sistema;


Algumas características do _processo_ devem ser determinadas para que o simulador opere adequadamente. Elas são:

1. _Tempo de chegada entre os processos_: O intervalo entre o tempo de chegada de cada _processo_ no sistema;
2. Requerimento de memória **CM** do processo;
3. _Tempo entre as requisições do **processo** _: O intervalo entre a associação do _processo_ ao **CPU** e a sua requisição de _I/O_. No **BASYS**, um _processo_ libera o **CPU** ao realizar uma requisição _I/O_; o tempo total de **CPU** utilizado  por um _processo_ é dividido pelas requisições _I/O_ num número de intervalos chamados _tempo de entre requisição_;
4. _Número de requisições **I/O** _: Que também determina o número de _tempos entre requisição_, e assim, o tempo total do _processo_ na **CPU**; 
5.  Duração da requisição _I/O_;

### Estrutura do Simulador

#### Eventos e Lista de Eventos
No simulador, um _processo_ é representado por uma tupla na _Tabela de Processos_. Essa entrada contém as características estabelecidas para aquele _processo_ em particular assim como muitos contadores para acumulação de estatísticas relativas ao _processo_. Enquanto o _processo_ atravessa o sistema, entra em filas, é assinalado ao **CPU**, etc.; seu movimento é refletido ao mover um ponteiro para a entrada na _Tabela de Processos_ correspondente ao _processo_, ao invés de mover a entrada como um todo.	

O progresso do _processo_ no sistema é marcado pela ocorrência de uma série de _**eventos**_. Esses _eventos_ correspondem a pontos de transição entre as operações ou atividades; eles representam uma **mudança de estado**. Alguns _eventos_ significativos podem ser:

* A associação de um _processo_ ao **CPU** (a mudança do estado de **"espera"** para **"execução"**;
* A liberação do **CPU** para esperar a conclusão de uma requisição _I/O_ (a mudança do estado de **"execução"** para **"espera"**);

É conveniente desenvolver o sistema de simulação para que haja uma correspondência um-para-um entre os _eventos_ do _modelo de simulação_ e as _rotinas do simulador_. Com esse modelo, cada _"rotina de evento"_ do simulador faz, essencialmente, duas coisas: realiza operações cuja iniciação correspondem a ocorrência do evento e prevê, para o _processo_ ao qual a operação foi realizada, qual o próximo _evento_ que ocorrerá e quando isso ocorrerá. Por exemplo, os passos básicos  na _rotina de evento_ **"Associar a CPU"** pode ser o seguinte:

* Marcar uma _flag_ avisando a associação do _processo_ ao **CPU**;
* Determinar (prever) o tempo no qual o _processo_ liberará o **CPU** e determinar o _evento_ que liberará o **CPU** (**"Finalizar execução"** ou **"Requisição de I/O"**);

Enquanto cada evento simulado ocorre, o tempo e a identidade do próximo evento a ocorrer para aquele _processo_ específico são determinados. No simulador, o processamento é uma operação semi-paralela, refletindo a verdadeira simultaneidade do sistema simulado. A duração prevista de uma operação é somada ao ao valor do tempo simulado no qual a operação foi iniciada para obter o ponto em tempo simulado no qual um _evento_ (o fim daquela operação em particular) deve ocorrer. Dessa forma, se fôssemos obter uma imagem do relógio (o atual valor da variável representando o tempo simulado) e uma tabulação dos _processos_ no sistema junto a identidade do próximo _evento_ e o próximo tempo de _evento_ para esses _processos_, em algum ponto aleatório da simulação os seguintes resultados poderiam aparecer:

**TEMPO:** 108075

|JOB (J)|NEXT EVENT (E)|EVENT TIME (T)|
|-------|--------------|--------------|
|63     |I/O ISSUE     | 110042       |
|22     |RELEASE CPU   | 110121       |
|88     |JOB ARRIVAL   | 124003       |


Isso reflete a simulação de diversas atividades paralelas. No entanto, a simulação só está preocupada com o início e o fim dessas atividades; esses pontos compreendem uma sequência de _eventos_, os quais tem sua ordem determinada pelos tempos os quais esses eventos devem ocorrer.

Estabelecer a sequência desses _eventos_ (**"escalonar"** os _eventos_) é facilitada pelo uso de uma _Lista de Eventos_, ainda que haja outras formas de chegar a isso. Num simulador _BASYS_, é assumido que essa lista seja uma _lista ligada_ com entradas de 4 elementos.

1. Identificador do Evento
2. Tempo do Evento
3. Ponteiro para a tupla na _Tabela de Processos_
4. Link para o próximo evento

Sempre que um evento novo é adicionado a _Lista de Eventos_, sua posição é determinada pelo item 2 _Tempo do Evento_; A lista é ordenada de forma ascendente de acordo com o _Tempo do Evento_.

Todas as _rotinas de evento_ no _BASYS_ fazem entradas na _Lista de Eventos_, mas apenas uma rotina (**O Escalonador**) remove as entradas dessa lista. Todas as transferências das rotinas são do **Escalonador** e todas as saídas das rotinas são para o **Escalonador**. Os passos básicos no escalonamento de _eventos_ são os seguintes:

1. O **Escalonador** remove a entrada no topo da _Lista de Eventos_. Essa entrada especifica um tempo de evento **T**, um identificador de evento **E** e um ponteiro para a _Tabela de Processos_ **J**;
2. O **Escalonador** avança o relógio (**TIME**) para o tempo do evento **T** especificado no primeiro passo, por que esse tempo representa o primeiro de todos os eventos escalonados para ocorrer;
3. O **Escalonador** transfere o controle para a _rotina de evento_ designada pelo identificador do evento **E**;
	4. A _rotina de evento_ realiza o processamento requerido para o _processo_, determina o próximo evento e seu tempo, e insere o identificador de evento (**E**), o tempo do evento (**T**), e o ponteiro para a _Tabela de Processos_ (**J**) _Lista de Eventos_. Então, o controle é retornado para o **Escalonador**.

O mecanismos de escalonamento de _eventos_ pode facilmente ser implementado em _Fortran_; linguagens contemporâneas orientadas a evento possuem facilidades similares.

É possível que o tempo para o próximo _evento_ de um _processo_ seja imprevisível. Assim, não haverá nenhuma entrada para esse _processo_ na _Lista de Eventos_. Isso ocorre, por exemplo, quando um _processo_ encontra algum dos mecanismos necessários a sua execução ocupados, e ele entra numa fila. Quando esse _evento_ ocorre, é impossível prever o tempo em que o _processo_ deixará a fila e entrará no mecanismo. Quando o mecanismo é liberado, um _processo_ é selecionado da fila de acordo com a _disciplina de fila_ apropriada e escalonado para o _evento_ no qual resultará em sua entrada no mecanismo. No simulador _BASYS_, todo o _processo_ no sistema é representado pela aparição de sua entrada da _Tabela de Processos_ na _Lista de Eventos_ ou em alguma fila, mas não em ambas. Isso não é uma regra geral; Suponha que o _processo_ não liberou o **CPU** ao realizar uma requisição _I/O_. Nesse caso, o ponteiro para a _Tabela de Processos_ pode aparecer duas vezes na _Lista de Eventos_ (uma para a completude da requisição _I/O_ e outra para realizar a próxima requisição _I/O_) ou então pode aparecer na _Lista de Eventos_ e na fila.

#### Filas

Outro uso de listas ligadas no simulador é a manutenção de filas. Na sua forma mais elementar, uma simples fila _FIFO_ pode ser mecanizada como uma lista ligada de dois elementos por entrada. Um elemento contendo o _ponteiro para a tabela de processos_ e o outro um link. O enfileiramente de um _processo_ seria então determinado ao adicionar uma entrada ao _final_ da lista. A remoção de um _processo_ seria determinado ao remover um item do _início_ da lista.

Um mecanismo mais útil seria capaz de determinar outras formas de administrar a fila além de _FIFO_, e também prover formas de coletar estatísticas quanto ao comportamento da fila.


___________________________________________________________________________________

### O Simulador _BASYS_

As rotinas de evento que descrevem o simulador _BASYS_ são descritas abaixo. 



**Evento 1**: Marca a chegada de um _processo_ ao sistema. As características desse _processo_ são determinadas pela amostra de distribuições apropriadas e armazenadas numa entrada na _Tabela de Processos_ apropriada para esse processo. (outro uso das listas no simulador é o armazenamento de entradas disponíveis na _Tabela de Processos_). Para a simulação do BASYS, as seguintes características de de _processo_ são geradas: 

* Espaço de memória necessário;
* Número de registros lidos/escritos;
* Tempo de CPU necessário;
* Tempo médio entre requisições;
* Tamanho do registro.

O próximo _evento_ para esse _processo_ é escalonado pela inserção da trinca: **1.** ponteiro da _Tabela de Processos_ (**J**), **2.** identificador de evento (**E**) e  **3.** tempo do evento na _Lista de Eventos_. No nosso modelo básico, não há atraso entre o tempo de chegada de um _processo_ ao sistema e o tempo em que ele requisita **CM**. Dessa forma, seria possível transferir diretamente para a rotina do _Evento 2_ ou combinar as rotinas do _Evento 1_ e _Evento 2_. Contudo, a organização descrita ajuda a expandir o simulador para que este possua, por exemplo, operações _card-to-disk_.

**Evento 2**: É a ocorrência  de uma requisição de _processo_ para espaço na **CM**. O tamanho de memória requerido pelo _processo_ (da _Tabela de Processos_) é comparado com o tamanho de memória disponível na **CM**. Se há espaço suficiente disponível, ele é alocado ao _processo_; em outro caso, o _processo_ entra na _Fila da CM_. É assumido que a alocação de espaço da _CM_ para um _processo_ deve requerir realocação de outros _processos_ para prover espaço contíguo suficiente para o _processo_ em questão. O próximo evento para esse _processo_ (_Evento 3_) é escalonado para ocorrer num tempo _igual_ ao tempo atual somado ao tempo requerido para realocar a **CM**. (Embora em um sistema real essa realocação necessite uma interrupção na **CPU**, isso não é feito nesse modelo básico. A implementação de interrupções no modelo será discutida mais tarde.

**Evento 3**: Corresponde a requisição de um _processo_ para utilizar o processador central **CPU**. Se o **CPU** estiver livre, ele é reservado para uso do _processo_ que o requisita; em outro caso, o _processo_ entra na _Fila do CPU_. O número de registros a serem lidos ou escritos 	e o tempo médio entre as requisições _I/O_ foram estabelecidos quando o _processo_ chegou. Se o contador de registros não foi reduzido a zero, uma amostra da distribuição apropriada com esse valor de média é usado para determinar o tempo no qual a próxima requisição _I/O_ será feita. A contagem de registros é decrementada e o _Evento 4_ (Liberar a **CPU** é escalonado para esse tempo. Se a contagem de registros chegar a zero, o _Event0 7_ (finalizar execução) é escalonado.

**Evento 4**: O _Evento 4_ é a liberação da **CPU** por um _processo_ que realizou uma requisição _I/O_. Quando o requisitor libera o **CPU**, a _Fila do CPU_ é examinada; se haver _processos_ esperando, um é selecionado da fila e escalonado para o _Evento 3_ (Requerir **CPU**). O _processo_ que está liberando o _CPU_ é escalonado para o _Evento 5_ (processar requisição _I/O_). Ambos os _processos_ são escalonados para ocorrer num tempo igual ao tempo atual somado  a um tempo de _overhead_ (**T0**) requerido para processar a requisição. Observe que a contagem desse tempo não é necessária, já que é possível combinar os eventos 4 e 5.

**Evento 5**: Marca a iniciação do processamento de uma requisição _I/O_. Se o **DISK** estiver ocupado, o _processo_ entra na _Fila de Disco_. Se o **DISK** estiver livre, ele é reservado para o _processo_ e o tempo de processamento da requisição _I/O_ é computado. Por exemplo, se posicionamento do **DISK** é requerido, o tempo de processamento pode ser dado por:

**Td = Tp + Tl + Tt . R**

Onde **Tp** é o tempo de posicionamento, **Tl** é o tempo de latência (uma fração de tempoe escolhida aleatoriamente de um _revolution time_), **Tt** é o tempo de transferência de disco por palavra, e **R** é o tamanho do registro em palavras. O próximo evento (_Evento 6_ 	, liberar disco) é escalonado para ocorrer num tempo igual ao tempo corrente somado ao **Td**.

**Evento 6**: É a completude do processamento de uma requisição I/O.	 O **DISK** é liberado e a _Fila de Disco_ é checada para verificar requisições pendentes. Se haver requisições pendentes, uma delas é removida da fila e escalonada para o _Evento 5_ (processar requisição _I/O_). O _processo_ que liberou o **DISK** é escalonado para o _Evento 3_ (requisitar **CPU**). Aqui, outra vez, tempo de _overhead_ é facilmente incorporado, se desejado.

**Evento 7**: Marca a completude de um _processo_. A **CPU** é liberada  e, caso haja algum _processo_ na _Fila do CPU_, um será removido e escalonado para o _Evento 3_. O espaço de **CM** reservado  para o _processo_ é liberado. Se há algum _processo_ na _Fila do CM_ que pode agora ser associado a **CM**, este é removido da fila e escalonado para o _Evento 2_.

Em algumas áreas, tais qual adicionar o tempo de _overhead_ e de realocação, a descrição busca ser descritiva ao invés de completa. Essas e outras funcionalidades (como operações do disco para a impressora) podem ser incorporadas ao modelo de diversas formas.

#### Interrupções

A expansão do modelo de simulação básica necessitará a incorporação de _interrupções_. Há inúmeros de tipos e níveis de sistemas de interrupções que podem ser encontrados hoje na prática. Nessa discussão, trataremos um único tipo: A interrupção da execução de um _processo_ que esteja no **CPU** por um _processo_ com **maior prioridade**. Muitas outras interrupções podem ser feitas de forma similar, se não igual.

Vamos retornar por um instante na descrição da rotina do _Evento 3_. Essa rotina processa a atribuição de um _processo_ ao **CPU**; ao retornar o controle para a rotina de escalonamento, o _processo_:

* Havia inserido a trinca: tempo do próximo evento, identificador do evento (**E**) e ponteiro para a _Tabela de Processos_ (**J**) na _Lista de Eventos_, e
* Modificado as quantidades apropriadas na entrada da _Tabela de Processos_ (exemplo, a contagem de registros), para refletir o processamento a ser feito durante esse intervalo.


Suponha que o próximo evento para esse _processo_ deve ocorrer num tempo **Ts**, mas o processador central (**CPU**) recebe preempção de um outro _processo_ num tempo mais cedo denominado **Tp** (**Ts** > **Tp**). O que temos que fazer para que esse processo seja interrompido e, tardiamente, resumido? (O _processo_ que preemptou o **CPU** deve ser processado de forma usual e não apresenta problemas específicos.)

Como resultado da preempção do processador central, a _Lista de Eventos_ agora contém uma entrada inválida; o evento escalonado para o _processo interrompido_ não vai acontecer no tempo determinado, então, é necessário cancelar esse _evento_. A entrada correspondente a ele na _Lista de Eventos_ deve ser localizada e removida (ou o identificador do _evento_ modificado para indicar um _evento nulo_). O método exato a ser empregado será determinado pela linguagem de simulação 	utilizada. Em geral, localizar a _entrada_ na lista de eventos necessita conhecimento tanto do _identificador do evento_ quanto do _identificador do processo_. Dessa forma, quando interrupções são simuladas, o simulador deve manter conhecimento de cada usuário dos mecanismos (**CPU**, **CM**, **DISK**).

Para manter a contagem de tempo do _processo_ correta, o tempo restante de **CPU** nesse intervalo (**Ts** - **Tp**) deve ser registrado; quando o _processo_ interrompido for reiniciado, ele será atribuído ao **CPU** durante esse período. É também necessário salvar o identificador do evento para o _evento_ que foi cancelado. O processo interrompido pode ser colocado numa _Lista de Interrupção_ ou na _Fila do CPU_, dependendo do design do sistema simulado. _Se o sistema 	 entrar na Fila do CPU_, ele deve ser marcado para que a rotina de evento possa distinguir entre _processos interrompidos_ e _processos novos ou retornando de espera I/O_. O _Evento 3_, ao processar _processos interrompidos_, realiza apenas os seguintes passos:

* Limpar a marcação de interrupção da entrada na _Tabela de Processos_;
* Obter tempo de computação remanescente e identificador de evento da _Tabela de Processos_;
* Reagendar (_Re-escalonar_) o evento a ocorrer para o tempo atual somado ao tempo de processamento remanescente.

_____________________________________________________________________________________

_Daqui para baixo pode ser opcional_


#### Implementando um simulador BASYS: linguagens de simulação

Há muitas linguagens de simulação, incorporando diversos conceitos básicos aos modelos de simulação, que existem hoje. Um excelente (embora não mais atual) artigo sobre linguagens de simulação foi preparado por _Teichroew e Lubin_. As linguagens de simulação mais amplamente acessíveis são a GPSS e o _SimScript_.
