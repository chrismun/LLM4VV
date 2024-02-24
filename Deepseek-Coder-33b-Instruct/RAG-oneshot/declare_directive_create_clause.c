#include <stdlib.h>
#include <openacc.h>

int main() {
    int *data_in_shared_memory = (int*)malloc(sizeof(int));
    int *data_not_in_shared_memory = (int*)malloc(sizeof(int));
    int *data_in_global_context = (int*)malloc(sizeof(int));

    *data_in_shared_memory = 1;
    *data_not_in_shared_memory = 2;
    *data_in_global_context = 3;

    #pragma acc data copyin(data_not_in_shared_memory, data_in_global_context)
    {
        #pragma acc declare create(data_in_shared_memory)

        // Test the behavior of data in shared memory
        if (*data_in_shared_memory != 1) {
            return 1; // Test failed
        }

        // Test the behavior of data not in shared memory
        if (*data_not_in_shared_memory != 2) {
            return 1; // Test failed
        }

        // Test the behavior of data in global context
        if (*data_in_global_context != 3) {
            return 1; // Test failed
        }
    }

    return 0; // Test passed
}