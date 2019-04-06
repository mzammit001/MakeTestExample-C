#include "queuer.h"

int main(void) {
    int test[TEST_LEN];

    for (int i = 0; i < TEST_LEN; ++i) {
        test[i] = i;
    }

    ring_queue_t *rq = init_ring_queue(30, sizeof(int));

    printf("before enqueue: length => %zd\n", length_ring_queue(rq));

    int ctr = 0;
    while (enqueue_ring_queue(rq, &test[ctr])) {
        ++ctr;
    }

    printf("after enqueue: length => %zd\n", length_ring_queue(rq));

    int tmp;
    while (dequeue_ring_queue(rq, &tmp)) {
        printf("dequeued: %d\n", tmp);
    }

    printf("after dequeue: length => %zd\n", length_ring_queue(rq));

    free_ring_queue(rq);

    return 0;
}