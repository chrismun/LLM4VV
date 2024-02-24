#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int *data;
    int err = 0;
    int ret;

    data = (int*)malloc(sizeof(int));
    *data = 10;

    #pragma acc enter data copyin(data[0:1])
    #pragma acc parallel present(data[0:1])
    {
    }
    #pragma acc exit data delete(data[0:1])

    ret = acc_is_present(data, sizeof(int));

    if (ret != 1) {
        err = 1;
        printf("acc_is_present failed\n");
    }

    free(data);

    return err;
}