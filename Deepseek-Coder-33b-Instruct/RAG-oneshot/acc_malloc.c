#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    const int size = 100;
    int *ptr = (int*)acc_malloc(size * sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Memory allocated successfully using acc_malloc.\n");

    acc_free(ptr);

    printf("Memory freed successfully using acc_free.\n");

    return 0;
}