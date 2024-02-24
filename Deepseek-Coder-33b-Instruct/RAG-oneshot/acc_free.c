#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *data_dev = (int*)acc_malloc(n * sizeof(int));

    if (data_dev == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory allocated successfully\n");

    acc_free(data_dev);

    printf("Memory freed successfully\n");

    return 0;
}