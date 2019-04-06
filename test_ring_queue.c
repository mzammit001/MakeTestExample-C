#include "test_ring_queue.h"

static int num_passed = 0;

void test_init_ring_queue() {
    ring_queue_t *rq = init_ring_queue(CAPACITY, ESIZE);

    if (rq == NULL || rq->buffer == NULL || rq->capacity != CAPACITY || rq->element_size != ESIZE) {
        FAILED_TEST(__func__);
        return;
    }
    
    PASSED_TEST(__func__);
    num_passed += 1;

    free_ring_queue(rq);
}

void test_length_ring_queue() {
    ring_queue_t *rq = init_ring_queue(CAPACITY, ESIZE);

    if (rq == NULL) {
        FAILED_TEST(__func__);
        return;
    }

    if (length_ring_queue(rq) != 0) {
        FAILED_TEST(__func__);
        free_ring_queue(rq);
        return;
    }

    for (int i = 0; i < CAPACITY / 2; ++i) {
        enqueue_ring_queue(rq, &i);
    }

    if (length_ring_queue(rq) != CAPACITY / 2) {
        FAILED_TEST(__func__);
        free_ring_queue(rq);
        return;
    }

    PASSED_TEST(__func__);
    num_passed += 1;

    free_ring_queue(rq);

}
void test_enqueue_ring_queue() {
    ring_queue_t *rq = init_ring_queue(CAPACITY, ESIZE);

    if (rq == NULL) {
        FAILED_TEST(__func__);
        return;
    }

    int ctr = 0;
    while (ctr < CAPACITY / 2) {
        if (enqueue_ring_queue(rq, &ctr) != &ctr) {
            FAILED_TEST(__func__);
            free_ring_queue(rq);
            return;
        }
        ++ctr;
    }

    if (length_ring_queue(rq) != CAPACITY / 2) {
        FAILED_TEST(__func__);
        free_ring_queue(rq);
        return;
    }

    PASSED_TEST(__func__);
    num_passed += 1;
    
    free_ring_queue(rq);
}
void test_dequeue_ring_queue() {
    ring_queue_t *rq = init_ring_queue(CAPACITY, ESIZE);

    if (rq == NULL) {
        FAILED_TEST(__func__);
        return;
    }

    for (int i = 0; i < CAPACITY / 2; ++i) {
        if (enqueue_ring_queue(rq, &i) != &i) {
            FAILED_TEST(__func__);
            free_ring_queue(rq);
            return;
        }
    }

    if (length_ring_queue(rq) != CAPACITY / 2) {
        FAILED_TEST(__func__);
        free_ring_queue(rq);
        return;
    }

    for (int i = 0; i < CAPACITY/2; ++i) {
        int tmp;
        if (dequeue_ring_queue(rq, &tmp) != &tmp || tmp != i) {
            FAILED_TEST(__func__);
            free_ring_queue(rq);
            return;
        }
    }

    if (length_ring_queue(rq) != 0) {
        FAILED_TEST(__func__);
        free_ring_queue(rq);
        return;
    }

    PASSED_TEST(__func__);
    num_passed += 1;
    
    free_ring_queue(rq);
}

void run_testsuite(int n_tests, ...) {
    va_list vlist;
    va_start(vlist, n_tests);

    for (int i = 0; i < n_tests; ++i) {
        testfunc_t ptest = va_arg(vlist, testfunc_t);
        ptest();
    }

    va_end(vlist);
}

int main(void) {
    int n_tests = 4;

    run_testsuite(n_tests,
                  test_init_ring_queue,
                  test_length_ring_queue,
                  test_enqueue_ring_queue,
                  test_dequeue_ring_queue);

    printf("%d / %d tests passed.\n", num_passed, n_tests);

    return 0;
}