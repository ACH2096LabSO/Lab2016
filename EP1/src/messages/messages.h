
//
// Created by brunno on 29/03/16.
//

#include "../simulador.h"
#include "../cpu/include/process_struct.h"
#include "../memory/include/central_memory.h"



#ifndef MESSAGES_H
#define MESSAGES_H

void printConfig();
void printProcess(process* proc, int printExecList);
void printProcessList(char* lineName, processLine pline,  int printExecList);
void printMemoryFrameQueue(FREE_FRAMES *freeFrames);
void printFrame(FRAME *fr);
void printMemoryMap(FRAME **memorymap);
void printOutOfMemory(int available, int required, int jobId);
void printFreedTables(int tables);
void printTransferMessage(char* action, int currenttime, processLine origin, processLine destination, process *p);

#endif //MESSAGES_H
