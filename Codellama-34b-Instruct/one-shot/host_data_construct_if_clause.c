#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test host_data construct with if clause
    #pragma acc host_data if(acc_device_nvidia)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 0);
        }
    }

    // Test host_data construct with if clause and device_type clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 1);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_gangs clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_gangs(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 2);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_workers clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_workers(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 3);
        }
    }

    // Test host_data construct with if clause and device_type clause and vector_length clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) vector_length(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 4);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_gangs clause and num_workers clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_gangs(4) num_workers(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 5);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_gangs clause and vector_length clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_gangs(4) vector_length(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 6);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_workers clause and vector_length clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_workers(4) vector_length(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 7);
        }
    }

    // Test host_data construct with if clause and device_type clause and num_gangs clause and num_workers clause and vector_length clause
    #pragma acc host_data if(acc_device_nvidia) device_type(acc_device_nvidia) num_gangs(4) num_workers(4) vector_length(4)
    {
        int x = 0;
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }
        if (x != 45) {
            failcode = failcode + (1 << 8);
        }
    }

    return failcode;
}