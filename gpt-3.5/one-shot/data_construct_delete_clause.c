#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int *data, *copy;

    data = (int*) malloc(N * sizeof(int));
    copy = (int*) malloc(N * sizeof(int));

    // Initialize data array
    #pragma acc parallel loop present(data)
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Copy data array to copy array
    #pragma acc parallel loop present(data, copy)
    for (i = 0; i < N; i++) {
        copy[i] = data[i];
    }

    // Delete data array
    #pragma acc data delete(data)

    // Verify that data is deleted and copy still contains the values
    int deleted = 0;
    for (i = 0; i < N; i++) {
        if (data[i] != 0) {
            deleted = 1;
            break;
        }
    }

    int verified = 1;
    for (i = 0; i < N; i++) {
        if (copy[i] != i) {
            verified = 0;
            break;
        }
    }

    if (deleted && verified) {
        printf("Delete clause is implemented correctly\n");
    } else {
        printf("Delete clause is not implemented correctly\n");
    }

    free(data);
    free(copy);

    return 0;
}