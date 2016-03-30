#include <stdio.h>
#include <stdlib.h>
#include "messages/messages.h"

///FIFO

///Estrutura para lista de processos

typedef struct reg{

    int Processo;
    int Tempo;

    struct reg *prox;

} Processo;



/// função principal
int main(){

    int procs; ///Quantidade de Processos

    procs = recebeProcessos();/// Recebe a quantidade de processos (Trocar pelas entradas)

    Processo pri;
    tempoProcessos(procs,&pri); ///Recebe tempo dos Processos

    calculoDeTempoDeEspera(procs,&pri); /// Realiza calculo do tempo de CPU

    return 0;
}


/*
  Função utilizada para receber parâmetros de entrada para teste.
  Mudar função para receber parâmetros de entrada do programa após definição
  da equipe de integração
*/
int recebeProcessos(){

    int x = 0;
    while(x == 0){
        printf("Quantos Processos?:");
        scanf("%d",&x);
        if(x == 0)printf("Erro,nenhum processo\n");
    }
    return x;
}
/*
    Salva o tempo de consumo de cada processo dentro da CPU. Função utilizada para testes
    Assim como a função anterior, deverá ser modificada após definição da equipe
    de integração.
*/

int tempoProcessos(int procs, Processo *first){
    int i;

    Processo *pri,*ult;
    pri = malloc (sizeof (Processo));
    printf("Tempo de consumo de CPU para cada Processo(CPU Burst):\n");

    for(i = 0;i<procs;i++){
        if(procs == 1 || i == 0){
            printf("Processo[%d]:",i+1);
            scanf("%d",&pri->Tempo);
            pri->Processo=0;
            ult = pri;
            ult->prox = NULL;
        }
        else{
            Processo *aux;
            aux = malloc (sizeof (Processo));
            printf("Processo[%d]:",i+1);
            scanf("%d",&aux->Tempo);
            aux->Processo = i;
            aux->prox = NULL;
            ult->prox = aux;
            ult = aux;
        }

    }

    *first = *pri;
    return 0;
}

/*Calculo do tempo de espera e respostas de todos os processos*/


int calculoDeTempoDeEspera(int procs,Processo *p){

    int espera[procs],resposta[procs],i,mediaEspera=0, mediaTempoResp=0;
    espera[0] = 0;
    Processo *aux;

    for(i=1;i<procs;i++) ///Calculo do tempo de espera
    {
        espera[i]=0;
        for (aux = p;((aux->Processo)<i)&&(aux != NULL);aux = aux->prox){
            espera[i]+=aux->Tempo;
        }
    }
	ret = sprintf(msg, "\nProcesso\t\tTempo de CPU\t\tTempo de Espera\t\tTempo de Resposta");
    generateLog(msg);
	printf(msg);

    ///Tempo de Respota
    aux = p;
    for(i=0;i<procs;i++)
    {
        resposta[i]=aux->Tempo+espera[i];
        mediaEspera+=espera[i];
        mediaTempoResp+=resposta[i];
		ret = sprintf(msg,"\nP[%d]\t\t\t%d\t\t\t%d\t\t\t%d",i+1,aux->Tempo,espera[i],resposta[i]);
		generateLog(msg);
        printf(msg);
        aux = aux->prox;
    }

    mediaEspera/=i;
    mediaTempoResp/=i;
	
    ret = sprintf(msg ,"\n\nTempo medio de espera: %d",mediaEspera);
	generateLog(msg);
	printf(msg);
	
	ret = sprintf(msg ,"\nTempo medio de resposta: %d",mediaTempoResp);
	generateLog(msg);
	printf(msg);

    return 0;
}
