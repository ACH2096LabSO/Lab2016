Simulador de Sistema Operacional
================================

Projeto e implementação de um simulador orientado a eventos

## Prazo

**30/03/2016** (quarta-feira) - **Entrega individual via Tidia (SOMENTE!)**

[Atividade no Tidia](http://www.tidia-ae.usp.br/portal/site/5d71f5e0-79d0-42d2-951d-23372616af29/page/29ac7446-2e91-4c03-8ebf-b0fdc0127e25)

## Material de entrega

- Relatório explicando a estrutura e o funcionamento de todas as partes do programa e explicação de sua participação na implementação, caso tenha feito de forma colaborativa;
- Código fonte documentado;
- Manual de compilação/execução.

## Algoritmos necessários 

- **CPU**: FCFS (*First-come, first-served*) e Round-robin;
- **Memória**: paginação (sem swap);
- **I/O**: FIFO (*First in, first out*).

## Estrutura planejada

![Diagrama da estrutura do projeto](projeto/estrutura.png?raw=true)

## Divisão do trabalho

|Eventos|Escalonadores|Arquivos|Memória|Integração e Saída|
|---|---|---|---|---|
|Felipe|Giovanni|João|Brunno|Alexandre|
|~~Edson~~|Pedro||Leo|~~Matheus~~|
|Victor|Adriano||Eduardo||
|Leonardo|||Gustavo||
|Juliane|

## Como compilar

```sh
$ make
```

## Como executar

```sh
$ ./bin/simulador [arquivo de entrada]
```
