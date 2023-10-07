#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,construct-independent,wait,2,ncopies,data_region,enter-data,V:2.0-2.7
int test1(){
    int err = 0;

    srand(SEED);
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:10*n])
    #pragma acc data copyin(a[0:10*n])
    {
      #pragma acc serial
      {
        for (int x = 0; x < 10; ++x){
          for (int y = 0; y < n; ++y){
            a[y + x * n] = 0;
          }
        }
      }
      #pragma acc serial
      {
        for (int x = 0; x < 10; ++x){
          for (int y = 0; y < n; ++y){
            a[y + x * n] += 1;
          }
        }
      }
      #pragma acc parallel
      {
        int is_present = 1; /* false */
        int devout = 0, devnull = 0;
  
        for (int x = 0; x < 10; ++x){
          devnull += (a[x * n] != 1.0);
          for (int y = 0; y < n; ++y){
            if (a[x * n + y] != 1.0){
              is_present = 0;
              ++devnull;
            }
          }
          if (is_present == 1){
            ++devout;
          }
          is_present = 1;
        }
  
        #pragma acc atomic reduction(+:err)
          err = devnull;
        devnull = 0;
        #pragma acc atomic reduction(+:err)
          err = devnull;
      }
    }
    #pragma acc exit data delete(a[0:10*n])

    return err;
}
#endif

#ifndef T2
//T2:runtime,data,construct-independent,wait,2,ncopies,enter-data,deviceonly,copyin,V:2.0-2.7
int test2(){
    int err = 0;
    if (acc_get_device_type() == acc_device_nvidia){
        real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));

        for (int x = 0; x < 10 * n; ++x){
            a[x] = 1;
        }

        #pragma acc enter data copyin(a[0:10*n])
        acc_set_device_num(acc_get_num_devices(acc_device_nvidia), acc_device_nvidia);
        acc_wait(acc_async_sync);
        #pragma acc parallel
        {
          for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
              a[y + x * n] += 1;
            }
          }
        }

        #pragma acc exit data copyout(a[0:10*n])

        for (int x = 0; x < 10; ++x){
          for (int y = 0; y < n; ++y){
            err += (fabs(a[y + x * n] - 2) > PRESENT_EPSILON);
          }
        }
        #pragma acc exit data delete(a[0:10*n])

        return err;
    }
    else {
        return 0;
    }
}
#endif

#ifndef T3
//T3:runtime,data,construct-independent,wait,2,ncopies,enter-data,hostonly,copyin,V:2.0-2.7
int test3(){
    int err = 0;

    if (acc_get_device_type() == acc_device_nvidia){
    real_t *a = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 1;
    }

    #pragma acc enter data copyin(a[0:10*n])
    acc_set_device_type(acc_device_host);
    acc_wait(acc_async_sync);
    #pragma acc parallel
    {
      for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
          a[y + x * n] += 1;
        }
      }
    }
    #pragma acc exit data copyout(a[0:10*n])

    for (int x = 0; x < 10; ++x){
      for (int y = 0; y < n; ++y){
        err += (fabs(a[y + x * n] - 2) > PRESENT_EPSILON);
      }
    }
    #pragma acc exit data delete(a[0:10*n])

    return err;
    }
    else {
        return 0;