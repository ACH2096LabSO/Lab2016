#include <stdlib.h>
#include "include/central_memory.h"

int init_mem(int num_frames, int frame_size)
{
    if (num_frames < 1 || frame_size < 1) return -2;
    if (FREE_FRAMES_QUEUE) return 0;

    FREE_FRAMES *queue = malloc(sizeof(FREE_FRAMES));
    if (!queue) return -1;

    int i;
    for (i = 0; i < num_frames; i = i + frame_size) {
        FRAME *frame = malloc(sizeof(FRAME));
        if (!frame) return -1;

        frame->frame_id = i;
        frame->next = NULL;

        if (!queue->head) {
            queue->head = frame;
        }

        if (queue->tail) {
            queue->tail->next = frame;
        }

        queue->tail = frame;
    }

    return 1;
}
