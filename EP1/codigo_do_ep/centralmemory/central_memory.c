#include <stdlib.h>
#include "include/central_memory.h"

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
    if (!aux_queue) return 0;

    int i;
    for (i = 0; i < num_frames; i++) {
        FRAME *frame = malloc(sizeof(FRAME));
        if (!frame) return 0;

        frame->id = i;
        frame->address = 0;
        frame->job_id = -1;
        frame->next = NULL;

        if (!aux_queue->head) {
            aux_queue->head = frame;
        }

        if (aux_queue->tail) {
            int last_address = aux_queue->tail->address;
            frame->address = last_address + frame_size;
            aux_queue->tail->next = frame;
        }

        aux_queue->tail = frame;
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
