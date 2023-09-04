#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_TEST_CALLS 10

typedef struct {
    int x;
    int y;
} point;

void acc_attach(point *ptr_addr) {
    // Do nothing
}

void acc_detach(point *ptr_addr) {
    // Do nothing
}

int main() {
    point p;
    p.x = 1;
    p.y = 2;

    acc_attach(&p);
    acc_detach(&p);

    return 0;
}