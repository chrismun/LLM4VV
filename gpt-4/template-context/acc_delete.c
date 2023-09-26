#include <stdio.h>
#include <openacc.h>

#define ARR_SIZE 100

void test_openacc_delete()
{
    int *data = malloc(sizeof(int) * ARR_SIZE); // allocate memory on the host
    int i;
    size_t bytes = sizeof(int) * ARR_SIZE;

    // initialise the data array
    for(i=0; i<ARR_SIZE; i++) {
        data[i] = i+1;
    }

    // allocate memory on device and copy data from host to device
    #pragma acc enter data copyin(data[0:ARR_SIZE]) 

    // delete data from device
    acc_delete(data, bytes);

    // Check if data receives 'acc_not_present' error when re-accessing it on device
    #pragma acc parallel loop present(data[0:ARR_SIZE]) 
    for(i=0; i<ARR_SIZE; i++) {
        data[i] *= 2;
    }

    // free memory on host
    free(data);
}

int main()
{
    test_openacc_delete();
    return 0;
}