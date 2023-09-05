#include <stdio.h>
#include <openacc.h>

int main() {
    float *data;
    int size = 1000;

    data = (float*) malloc(sizeof(float) * size);

    for(int i = 0; i < size; i++) {
        data[i] = 1.0;
    }

    acc_init(acc_device_default);

    int num_devices = acc_get_num_devices(acc_device_default);
    printf("Number of devices: %d\n", num_devices);

    if(num_devices > 0) {
        #pragma acc data copy(data[0:size]) 
        {
            #pragma acc kernels 
            for(int i = 0; i < size; i++) {
                data[i] *= 2.0;
            }
        }
    }

    acc_shutdown(acc_device_default);
    
    for(int i = 0; i < size; i++) {
        if(data[i] != 2.0) {
            printf("Test failed.\n");
            free(data);
            return 1;
        }
    }

    printf("Test passed.\n");
    free(data);
    return 0;
}