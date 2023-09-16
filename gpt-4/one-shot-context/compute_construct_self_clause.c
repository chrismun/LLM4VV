#include <stdio.h>
#include <openacc.h>

int main() {
    int device_num = 0;
    int array[100];
    int error = 0;

    // Initialize array:
    for (int i = 0; i < 100; i++) {
        array[i] = i;
    }

    // Use the self clause to run the loop on the host even though we are in a data construct:
    #pragma acc data copy(array)
    {
        #pragma acc parallel loop self(device_num)
        for (int i = 0; i < 100; i++) {
            array[i] = array[i] * 2;
        }
    }

    // Verify results:
    for (int i = 0; i < 100; i++) {
        if (array[i] != i * 2) {
            error = 1;
            printf("Error at array[%d]. Expected %d but got %d\n", i, i*2, array[i]);
        }
    }

    if (error != 0){
        printf("Test failed.\n");
        return -1;
    }
    else{
        printf("Test passed.\n");
        return 0;
    }
}