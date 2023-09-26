#include <stdio.h>
#define SIZE 100
#define ACC_ASYNC_NO1 1
#define ACC_ASYNC_NO2 2

int main()
{
    float a[SIZE], b[SIZE], c[SIZE];

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = i;
    }

    int queue_array[2] = { ACC_ASYNC_NO1, ACC_ASYNC_NO2 };
    bool test_pass = true;

    #pragma acc data copyin(a[0:SIZE], b[0:SIZE]) copyout(c[0:SIZE])
    {
        #pragma acc parallel loop async(ACC_ASYNC_NO1)
        for(int i = 0; i < SIZE/2; ++i) {
            c[i] = a[i] + b[i];
        }

        #pragma acc parallel loop async(ACC_ASYNC_NO2)
        for(int i = SIZE/2; i < SIZE; ++i) {
            c[i] = a[i] + b[i];
        }

        int waiting_on = acc_wait_any(2, queue_array);

        if (waiting_on != -1) {
            printf("Waited on async operation %d\n", queue_array[waiting_on]);
        } else {
            test_pass = false;
        }
    }

    if (test_pass) {
        for(int i = 0; i < SIZE; ++i) {
            if(c[i] != 2*i) {
                printf("Test failed at index %d! Expected: %f, Got: %f\n", i, 2*i, c[i]);
                return -1;
            }
        }
        printf("Test passed!\n");
    } else {
        printf("Test failed: acc_wait_any returned -1\n");
    }

    return 0;