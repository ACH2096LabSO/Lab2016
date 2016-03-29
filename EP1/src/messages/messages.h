
//
// Created by brunno on 29/03/16.
//

#include "../simulador.h"
#include "../cpu/include/process_struct.h"



#ifndef MESSAGES_H
#define MESSAGES_H

    void printConfig();
    void printProcess(process* proc);
    void printProcessList(char* lineName, processLine pline);

#endif //MESSAGES_H
