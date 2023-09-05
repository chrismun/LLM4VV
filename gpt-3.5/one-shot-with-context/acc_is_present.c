#include <stdio.h>
#include <openacc.h>

int main() {
    int data[10];

    #pragma acc data copy(data[0:10])
    {
        printf("Is data present on the device? %s\n", acc_is_present(data, sizeof(data)) ? "Yes" : "No");
    }

    return 0;