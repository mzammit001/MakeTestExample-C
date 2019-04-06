#ifndef TEST_RING_QUEUE_H
#define TEST_RING_QUEUE_H

#include <stdio.h>
#include <stdarg.h>
#include "ring_queue.h"

#define PASSED_TEST(s) { printf("passed: %s\n", s); }
#define FAILED_TEST(s) { printf("failed: %s\n", s); }

#define CAPACITY (20)
#define ESIZE (sizeof(int))

typedef void (*testfunc_t)(void);

void test_init_ring_queue();
void test_length_ring_queue();
void test_enqueue_ring_queue();
void test_dequeue_ring_queue();

void run_testsuite(int n_tests, ...);

#endif