#include <stdio.h>
#include <openacc.h>

// Dummy precision value for the test
#define PRECISION 0.00001

int main() {
    int initial_default_async, modified_default_async;
    int err = 0;

    // Initialize the OpenACC runtime (optional, depending on the OpenACC runtime behavior)
    acc_init(acc_device_default);

    // Get the initial default async value
    initial_default_async = acc_get_default_async();
    printf("Initial default async: %d\n", initial_default_async);

    // Set a different value to the default async queue
    // Note: The specific number (e.g., 5) may need to be adjusted depending on the
    // implementation details and limitations (e.g., number of async queues supported).
    acc_set_default_async(5);

    // Get the modified default async value
    modified_default_async = acc_get_default_async();
    printf("Modified default async: %d\n", modified_default_async);

    // Verify if the default async value has been changed as expected
    if (modified_default_async == 5) {
        printf("Verification passed: The default async value was successfully modified.\n");
    } else {
        printf("Verification failed: The default async value was not modified as expected.\n");
        err = 1; // Indicate an error occurred
    }

    // Optionally, reset the default async queue to its initial value
    acc_set_default_async(initial_default_async);

    // Finalize the OpenACC runtime (optional, depending on the OpenACC runtime behavior)
    acc_shutdown(acc_device_default);

    return err; // Return 0 if successful, non-zero if an error occurred
}