#ifndef RING_QUEUE_H
#define RING_QUEUE_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define EXIT_ON_ERROR(s) \
    { \
        perror(s); \
        exit(1); \
    }

typedef struct ring_queue_s { 
    void *buffer;
    void *read_ptr;
    void *write_ptr;
    size_t element_size;
    size_t capacity;
    size_t length;
} ring_queue_t;

static inline void* get_endptr(ring_queue_t *rq);
ring_queue_t* init_ring_queue(size_t capacity, size_t element_size);
void free_ring_queue(ring_queue_t *rq);
void* dequeue_ring_queue(ring_queue_t *rq, void *out_element);
void* enqueue_ring_queue(ring_queue_t *rq, void *in_element);
size_t length_ring_queue(ring_queue_t *rq);

#endif