#include <stdlib.h>
#include "include/central_memory.h"

int init_mem(int num_frames, int frame_size)
{
    if (num_frames < 1 || frame_size < 1) return -2;
    if (FREE_FRAMES_QUEUE) return 0;

    FREE_FRAMES *queue = malloc(sizeof(FREE_FRAMES));
    if (!queue) return -1;

    int i;
    for (i = 0; i < num_frames; i++) {
        FRAME *frame = malloc(sizeof(FRAME));
        if (!frame) return -1;

        frame->id = i;
        frame->address = 0;
        frame->next = NULL;

        if (!queue->head) {
            queue->head = frame;
        }

        if (queue->tail) {
            int last_address = queue->tail->address;
            frame->address = last_address + frame_size;
            queue->tail->next = frame;
        }

        queue->tail = frame;
        queue->length++;
    }

    FREE_FRAMES_QUEUE = queue;

    return 1;
}
