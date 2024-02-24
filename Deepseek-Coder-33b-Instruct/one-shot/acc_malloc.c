#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *ptr = NULL;

    // Allocate memory using acc malloc
    ptr = (int*)acc_malloc(SIZE * sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate memory using acc_malloc\n");
        return 1;
    }

    // Initialize the memory
    for (int i = 0; i < SIZE; i++) {
        ptr[i] = i;
    }

    // Print the memory
    printf("Memory contents:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // Free the memory
    acc_free(ptr);

    return 0;
}