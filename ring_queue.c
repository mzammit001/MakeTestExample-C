#include "ring_queue.h"

// internal helper
inline void* get_endptr(ring_queue_t *rq) {
    return rq->buffer + (rq->capacity * rq->element_size);
}

/**
 * initialise the ring queue
 * 
 * params:
 * size_t capacity: the maximum capacity of the queue
 * size_t element_size: the size of the elements stored in the queue
 * 
 * returns:
 * ring_queue_t*
 */ 
ring_queue_t* init_ring_queue(size_t capacity, size_t element_size) {
    if (capacity == 0 || element_size == 0)
        return NULL;
    
    ring_queue_t *rq = malloc(sizeof(ring_queue_t));

    if (rq == NULL)
        EXIT_ON_ERROR("malloc failed: allocating queue");
    
    rq->buffer = malloc(element_size * capacity);

    if (rq->buffer == NULL)
        EXIT_ON_ERROR("malloc failed: allocating buffer");

    rq->capacity = capacity;
    rq->element_size = element_size;
    rq->length = 0;
    rq->read_ptr = rq->write_ptr = rq->buffer;

    return rq;
}

/**
 * free the ring queue
 * 
 * params:
 * ring_queue_t* : ring queue to free
 * 
 * returns:
 */ 
void free_ring_queue(ring_queue_t *rq) {
    if (rq != NULL) {
        free(rq->buffer);
        free(rq);
    }
}

/**
 * dequeue an element
 * 
 * params:
 * ring_queue_t* : ring queue
 * void* : pointer to some memory to store the dequeued element
 * 
 * returns:
 * NULL if empty, or out_element
 */ 
void* dequeue_ring_queue(ring_queue_t *rq, void *out_element) {
    // rq->write_ptr == rq->read_ptr when its empty
    if (rq == NULL || rq->length == 0)
        return NULL;

    // copy the element to the out_element ptr
    memcpy(out_element, rq->read_ptr, rq->element_size);
    // increment the read pointer
    rq->read_ptr += rq->element_size;
    // wraparound if we've reached the end of the array
    if (rq->read_ptr == get_endptr(rq))
        rq->read_ptr = rq->buffer;

    --rq->length;

    return out_element;    
}

/**
 * enqueue an element
 * 
 * params:
 * ring_queue_t* : ring queue
 * void* : pointer to some memory to read the enqueued element from
 * 
 * returns:
 * NULL if full, or in_element
 */ 
void* enqueue_ring_queue(ring_queue_t *rq, void *in_element) {
    // queue is full
    if (rq->length == rq->capacity)
        return NULL;
    
    // enqueue the element
    memcpy(rq->write_ptr, in_element, rq->element_size);
    // increment the write_ptr
    rq->write_ptr += rq->element_size;
    // wraparound
    if (rq->write_ptr == get_endptr(rq))
        rq->write_ptr = rq->buffer;

    ++rq->length;

    return in_element;
}

/**
 * get the current length of the ring queue
 * 
 * params:
 * ring_queue_t* : ring queue
 * 
 * returns:
 * size_t: length of current queue
 */ 
size_t length_ring_queue(ring_queue_t *rq) {
    if (rq == NULL)
        return 0;

    return rq->length;
}