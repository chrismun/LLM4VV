#include "acc_testsuite.h"
#ifndef T1
//T1:serial,loop,combined-constructs,V:2.7-2.7
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_host);

    int device_test1 = 0;
    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(1) private(device_test1)
    {
      device_test1 = 1;
    }

    if (device_test1 == 0){
        n = acc_get_num_devices(acc_device_host);
        acc_set_device_num(n, acc_device_host);
    }

    int * a = (int *)malloc(n * PRESENT_DEVICE_TYPE * sizeof(int));
    int * b = (int *)malloc(n * PRESENT_DEVICE_TYPE * sizeof(int));
    int prevhost = 1;
    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        if (a[x] > 0){
            prevhost = 0;
        }
        a[x] = -1;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n*PRESENT_DEVICE_TYPE]) copyout(b[0:n*PRESENT_DEVICE_TYPE])
    {
      #pragma acc serial copyin(a[0:n*PRESENT_DEVICE_TYPE]) copyout(b[0:n*PRESENT_DEVICE_TYPE])
      {
          #pragma acc loop
          for (int y = 0; y < PRESENT_DEVICE_TYPE; ++y){
              for (int x = 0; x < n; ++x){
                  b[x * PRESENT_DEVICE_TYPE + y] = a[x * PRESENT_DEVICE_TYPE + y];
              }
          }
      }
    }
    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        if (b[x] != -1){
            err += 1;
        }
    }

    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        b[x] = 0;
    }
    
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < PRESENT_DEVICE_TYPE; ++y){
            a[x * PRESENT_DEVICE_TYPE + y] = rand() % 10;
        }
    }

    #pragma acc data copyin(a[0:n*PRESENT_DEVICE_TYPE]) copyout(b[0:n*PRESENT_DEVICE_TYPE])
    {
      #pragma acc serial copyin(a[0:n*PRESENT_DEVICE_TYPE]) copyout(b[0:n*PRESENT_DEVICE_TYPE])
      {
          #pragma acc loop
          for (int y = 0; y < PRESENT_DEVICE_TYPE; ++y){
              #pragma acc loop
              for (int x = 0; x < n; ++x){
                  b[x * PRESENT_DEVICE_TYPE + y] = a[x * PRESENT_DEVICE_TYPE + y];
              }
          }
      }
    }

    int found = 0;

    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        found = 0;
        for (int y = 0; y < n; ++y){
            if (found != 1 && b[x] == a[y * PRESENT_DEVICE_TYPE]){
                found = 1;
            }
        }
        if (found == 0){
            err = 1;
        }
        found = 0;
    }

    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        found = 0;
        for (int y = 0; y < n; ++y){
            if (found != 1 && b[x] == a[y * PRESENT_DEVICE_TYPE + x%PRESENT_DEVICE_TYPE]){
                found = 1;
            }
        }
        if (found == 0){
            err = 1;
        }
        found = 0;
    }

    int host = 1;
    for (int x = 0; x < n * PRESENT_DEVICE_TYPE; ++x){
        if (b[x] > 0){
            host = 0;
        }
    }
    if (host != 1 && PRESENT_DEVICE_TYPE == 2){
        int passed = 0;
        for (int x = 0; x < n; ++x){
            if (passed != 1){
                if (b[x * 2] == a[x * 2] || b[x * 2 + 1] == a[x * 2 + 1]){
                    passed = 1;
                }
            }
        }
        if (passed != 1){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}