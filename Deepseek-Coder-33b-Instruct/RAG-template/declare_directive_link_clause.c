#include <stdio.h>
#include <stdlib.h>

#pragma acc routine seq
void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    const int size = 10;
    int *array = (int*)malloc(size * sizeof(int));

    #pragma acc parallel loop copy(array[0:size]) link(array)
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    print_array(array, size);

    free(array);

    return 0;
}