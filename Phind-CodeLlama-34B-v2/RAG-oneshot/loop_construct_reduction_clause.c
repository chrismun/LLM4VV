#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 1000

int main() {
    int i;
    int a = 0;
    int *b = (int *)malloc(NUM * sizeof(int));

    for (i = 0; i < NUM; i++) {
        b[i] = 0;
    }

    #pragma acc parallel loop reduction(+:a)
    for (i = 0; i < NUM; i++) {
        a += 1;
        b[i] += 1;
    }

    printf("a = %d\n", a);
    printf("b[0] = %d\n", b[0]);
    printf("b[%d] = %d\n", NUM-1, b[NUM-1]);

    free(b);
    return 0;
}