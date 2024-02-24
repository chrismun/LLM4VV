#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int data;
    int result;

    // Initialize data
    data = 42;

    // Test if data is accessible from the current device
    result = acc_is_present(&data, sizeof(data));

    if (result) {
        printf("acc_is_present: Data is accessible from the current device.\n");
    } else {
        printf("acc_is_present: Data is not accessible from the current device.\n");
    }

    return 0;
}