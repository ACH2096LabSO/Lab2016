//
// Created by brunno on 29/03/16.
//

#include "messages.h"
#include "../entrada/entrada.h"


void printConfig(){

#ifdef _MESSAGES_

	
	ret = sprintf(msg,"%s\n", "Config Options");
	generateLog(msg);
    printf("%s\n", msg);
	
	ret = sprintf(msg,"%s %i\n", "Tam Memoria:",mainMemorySize);
	generateLog(msg);
    printf("%s\n", msg);
	
	ret = sprintf(msg,"%s %i\n", "Tam Quadros de Memoria:",mainMemoryPageSize);
	generateLog(msg);
    printf("%s\n", msg);
	
	ret = sprintf(msg,"%s %i\n", "Time Slice CPU:",cpuTimeSlice);
	generateLog(msg);
    printf("%s\n", msg);
	
	ret = sprintf(msg,"%s %i\n", "Duracao de IO:",ioTimeDuration);
	generateLog(msg);
    printf("%s\n", msg);
	
	ret = sprintf(msg,"%s %i\n", "Num Processsos:",numProcessos);
	generateLog(msg);
    printf("%s\n", msg);
#endif


}


void printProcess(process* proc, int printExecList){

#ifdef _MESSAGES_
	ret = sprintf(msg,"%s %i %s %i %s %i %s %i %s %i %s %i %s %i\n", "Processo:", proc->ID, "Arrive Time:", proc->arrive_time, "CPU Burst:", proc->CPU_burst, "CPU Used:", proc->CPU_used, "Memory:", proc->memory, "Total IO:", proc->I_O, "IO Used:", proc->I_O_used);
	generateLog(msg);
    printf("%s \n", msg);
    if (printExecList==1){
        processExecList *p = proc->processList;
        while (p!=NULL){
			ret = sprintf(msg,"%s %i %s %i\n", "     Exec:", p->ID, "Type:", p->type);
			generateLog(msg);
            printf("%s \n", msg);
            p=p->next;
        }
    }

#endif

}

void printProcessList(char* lineName, processLine pline, int printExecList){


#ifdef _MESSAGES_
	ret = sprintf(msg,"%s %s %s\n", "Lista de Processos da lista", lineName, "em ordem");
	generateLog(msg);
    printf("%s \n", msg);
    if (pline.first==NULL) return;
    process *p = pline.first;
    while (p!=NULL){
        printProcess(p, printExecList);
        p=p->next;
    }
#endif


}


void printMemoryFrameQueue(FREE_FRAMES *freeFrames){

#ifdef _MESSAGES_
	
    if (freeFrames->head==NULL) return;
    FRAME *f = freeFrames->head;
	ret = sprintf(msg,"%s %i\n", "Imprimindo Lista de Frames - tamanho vazio - ", freeFrames->length);
	generateLog(msg);
    printf("%s \n", msg);
    while(f!=NULL){
		ret = sprintf(msg,"%s ", "Lista de frames");
		generateLog(msg);
		printf("%s \n", msg);
        printFrame(f);
        f= f->next;
    }
#endif
}

void printFrame(FRAME *fr){
#ifdef _MESSAGES_
    if (fr!=NULL)
		ret = sprintf(msg,"%s %i %s %i %s %i\n", "Frame:", fr->id, "Adress:", fr->address, "Job:", fr->job_id);
		generateLog(msg);
        printf("%s \n", msg);
    else
		ret = sprintf(msg,"%s \n", "Frame NULL");
		generateLog(msg);
        printf("%s \n", msg);
#endif
}


void printMemoryMap(FRAME **memorymap){
#ifdef _MESSAGES_
    int i;
	ret = sprintf(msg,"%s \n", "Imprimindo Mapa da memoria");
	generateLog(msg);
    printf("%s \n", msg);
    for(i=0;i<mainMemorySize;i++){
		ret = sprintf(msg,"%s %i ", "Local no mapa ", i);
		generateLog(msg);
        printf("%s \n", msg);
        printFrame(memorymap[i]);
    }

#endif
}

void printOutOfMemory(int available, int required, int jobId){
#ifdef _MESSAGES_
	ret = sprintf(msg,"%s %i %s %i %s %i\n", "Não há memória - Disponível:", available, "Requerida:", required, "Processo:", jobId);
    generateLog(msg);
    printf("%s \n", msg);
#endif
}

void printFreedTables(int tables)
{
#ifdef _MESSAGES_
	ret = sprintf(msg, "%s %i\n", "Quadros liberados", tables);
    generateLog(msg);
    printf("%s \n", msg);
#endif
}

void printTransferMessage(char* action, int currenttime, processLine origin, processLine destination, process *p){
#ifdef _MESSAGES_
	ret = sprintf(msg,"%s %i %s %i %s %s %s %s %s %s \n", "Tempo:", currenttime, "Processo:", p->ID, "movido de", origin.name, "para", destination.name, "Motivo:", action);
    generateLog(msg);
	printf("%s \n", msg);
#endif
}

void generateLog(char* text){
#ifdef _MESSAGES_
    FILE *f = fopen("log.txt", "w+");
if (f == NULL)
{
    printf("Error opening file!\n");
}
	fprintf(f, "%s\n", ,text);
	fclose(f);
#endif
}

void generateResult(int currenttime, processLine pline){
#ifdef _MESSAGES_
    FILE *f = fopen("result.txt", "w+");
	int dif;
if (f == NULL)
{
    printf("Error opening file!\n");
}
	if (pline.first==NULL) return;
	fprintf(f, "%s %i \n \n","Tempo atual: " , currenttime);
	fprintf(f, "%s \t %s \t %s" , "ID do processo Atual", "ID do próximo evento", "Tipo do próximo evento");
	fprintf(f, "%s \n", "");
	processExecList *p = proc->processList;
        while (p!=NULL){
			ret = sprintf(msg,"%i \t  %i \t %i", p->ID, p->next->ID, p->next->type);
			generateLog(msg);
            printf("%s \n", msg);
            p=p->next;
        }
	fclose(f);
#endif
}
