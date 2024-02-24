#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *data = (int*)malloc(n * sizeof(int));

    #pragma acc data copyin(data[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                data[i] = i;
            }
        }
    }

    if (acc_is_present(data, n * sizeof(int)) == 1) {
        printf("Data is present in the device memory.\n");
    } else {
        printf("Data is not present in the device memory.\n");
    }

    free(data);
    return 0;
}