#include <stdlib.h>
#include "include/central_memory.h"
#include "../entrada/entrada.h"
#include "../messages/messages.h"


int init_mem(int num_frames, int frame_size)
{
    if (num_frames < 1 || frame_size < 1) return -2;
    if (FREE_FRAMES_QUEUE) return 0;

    FREE_FRAMES *queue = NULL;
    if (!init_queue(&queue, num_frames, frame_size)) {
        return -1;
    }
    FREE_FRAMES_QUEUE = queue;

    FRAME **aux = NULL;
    if (!init_map(&aux, num_frames)) return -1;
    MEMORY_MAP_TABLE = aux;


    return 1;
}

int init_queue(FREE_FRAMES **queue, int num_frames, int frame_size)
{
    if (num_frames < 1 || frame_size < 1 || !queue) return 0;

    FREE_FRAMES *aux_queue = malloc(sizeof(FREE_FRAMES));
    aux_queue->head=NULL;
    aux_queue->length=0;
    aux_queue->tail=NULL;


    if (!aux_queue) return 0;

    int i;
    for (i = 0; i < num_frames; i++) {
        FRAME *frame = malloc(sizeof(FRAME));
        if (!frame) return 0;

        frame->id = i;
        frame->address = 0;
        frame->job_id = -1;
        frame->next = NULL;

        if (aux_queue->head==NULL) {
            aux_queue->head = frame;
            aux_queue->tail=  frame;
        }
        else{

            if (aux_queue->tail) {
                int last_address = aux_queue->tail->address;
                frame->address = last_address + frame_size;
                aux_queue->tail->next = frame;
            }

            aux_queue->tail = frame;
        }


        aux_queue->length++;
    }

    *queue = aux_queue;

    return 1;
}

int init_map(FRAME ***map, int num_frames)
{
    if (num_frames < 1|| !map) return 0;

    FRAME **aux = malloc(num_frames * sizeof(FRAME*));
    if (!aux) return 0;

    *map = aux;

    return 1;
}


int framesNeeded(int size){
    int num_frames = size / mainMemoryPageSize;
    if (size % mainMemoryPageSize) num_frames++;
    return  num_frames;
}

int allocate_mem(int size, int job_id)
{
    if (size < 1 || job_id < 0) return -1;
    if (!FREE_FRAMES_QUEUE || !MEMORY_MAP_TABLE) return -1;

    int num_frames = framesNeeded(size);

    int free_frames = FREE_FRAMES_QUEUE->length;
    if (free_frames < num_frames) {
        printOutOfMemory(FREE_FRAMES_QUEUE->length, num_frames, job_id);
        return 0;
    }

    int counter = num_frames;
    while (FREE_FRAMES_QUEUE->head && counter) {
        FRAME *frame = FREE_FRAMES_QUEUE->head;
        FREE_FRAMES_QUEUE->head = frame->next;

        frame->job_id = job_id;
        frame->next = NULL;

        MEMORY_MAP_TABLE[frame->id] = frame;
        FREE_FRAMES_QUEUE->length--;

        counter--;
    }

    if (!FREE_FRAMES_QUEUE->length) {
        FREE_FRAMES_QUEUE->tail = NULL;
    }

    return 1;
}

void free_mem(int job_id)
{
    if (job_id < 0 || !MEMORY_MAP_TABLE || !FREE_FRAMES_QUEUE) {
        return;
    }

    int i;
    int freetables=0;
    for (i = 0; i < mainMemorySize; i++) {
        if (!MEMORY_MAP_TABLE[i]) continue;
        if (MEMORY_MAP_TABLE[i]->job_id != job_id) continue;

        FRAME *frame = MEMORY_MAP_TABLE[i];
        frame->job_id = -1;


        if (!FREE_FRAMES_QUEUE->head) {
            FREE_FRAMES_QUEUE->head = frame;
        }

        if (FREE_FRAMES_QUEUE->tail) {
            FREE_FRAMES_QUEUE->tail->next = frame;
        }

        FREE_FRAMES_QUEUE->tail = frame;
        FREE_FRAMES_QUEUE->length++;

        MEMORY_MAP_TABLE[i] = NULL;
        freetables++;
    }
    printFreedTables(freetables, job_id);


}
