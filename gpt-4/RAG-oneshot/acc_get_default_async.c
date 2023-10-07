#include <stdio.h>
#include <openacc.h>

//helper function
void switch_default_async(int new_val) {
    acc_set_default_async(new_val);
    int changed_val = acc_get_default_async();
    if (new_val != changed_val) {
        printf("ERROR: Default async value not changed as expected. Should be %d, but got %d.\n", new_val, changed_val);
    } else {
        printf("PASSED: Default async value correctly changed to %d.\n", new_val);
    }
}

int main() {
    printf("\n*** Testing OpenACC acc_get_default_async function ***\n");

    // Ensure the current default async value is 0
    int default_async_val = acc_get_default_async();
    if (default_async_val != 0) {
        printf("ERROR: Initial default async value not 0.\n");
        return 1;
    } else {
        printf("PASSED: Initial default async value is 0.\n");
    }

    // Test changing the default async value
    switch_default_async(1);
    switch_default_async(0);

    printf("*** Test Complete ***\n");
    return 0;
}