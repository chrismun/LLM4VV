#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void acc_update_device(void *data_arg, size_t bytes);
void acc_update_self(void *data_arg, size_t bytes);

int main() {
    int size = 10;
    int *data = (int*)malloc(size * sizeof(int));

    #pragma acc data pcopy(data[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }

        #pragma acc update_self(data[0:size])
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    free(data);

    return 0;
}