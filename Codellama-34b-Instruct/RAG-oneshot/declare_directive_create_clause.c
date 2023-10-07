#include <openacc.h>

int main() {
    int failcode = 0;
    int failed;

    // Create a shared memory region
    acc_create_shared_memory(1024, 1024, 1024);

    // Declare a variable in shared memory
    int *a = (int *)acc_malloc(1024);

    // Initialize the variable
    for (int i = 0; i < 1024; i++) {
        a[i] = i;
    }

    // Create a device memory region
    acc_create_device_memory(1024, 1024, 1024);

    // Declare a variable in device memory
    int *b = (int *)acc_malloc(1024);

    // Initialize the variable
    for (int i = 0; i < 1024; i++) {
        b[i] = i;
    }

    // Create a structured reference counter for the variable
    acc_create_structured_reference_counter(a, 1);

    // Create a dynamic reference counter for the variable
    acc_create_dynamic_reference_counter(b, 1);

    // Perform a present increment action on the variable
    acc_present_increment(a, 1);

    // Perform a present decrement action on the variable
    acc_present_decrement(a, 1);

    // Perform a create action on the variable
    acc_create(b, 1);

    // Perform a delete action on the variable
    acc_delete(b, 1);

    // Check the structured reference counter
    if (acc_get_structured_reference_counter(a) != 0) {
        failcode = failcode + (1 << 0);
    }

    // Check the dynamic reference counter
    if (acc_get_dynamic_reference_counter(b) != 0) {
        failcode = failcode + (1 << 1);
    }

    // Free the memory
    acc_free(a);
    acc_free(b);

    return failcode;
}