#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,construct-independent,async,wait-acc-deps,devonly,devCtrls,memMapAsync*//*#PS11*/
//No explicit test directive to allow execution in kernels in addition to construct independent tests
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

int test1(real_t *dev_ptr, long long int deviceIdx, long long int *host_ptr){
    int err = 0;
    long long int i, j, prev_j;
    real_t temp;
    real_t *host_copy;

    if (host_ptr == NULL){
        host_copy = (long long int *)malloc(10 * n * sizeof(long long int));
        host_ptr = (long long int *)host_copy;
    }
    else{
        host_copy = (long long int *)malloc(10 * n * sizeof(long long int));
        for (i = 0; i < 10 * n; ++i){
            host_copy[i] = host_ptr[i];
        }
    }

    #pragma acc enter data copyin(host_copy[0:10*n])
    for (j = 0; j < 10; ++j){
        #pragma acc parallel async(deviceIdx) num_gangs(1) present(dev_ptr[0:5*n]) deviceptr(dev_ptr)
        #pragma acc loop vector collapse(2) independent
            for (i = 0; i < n; ++i){
                dev_ptr[j * n + i] = (real_t) i + (real_t) host_copy[j * n + i];
        }
    }

    prev_j = 0;
    for (j = 1; j < 10; ++j){
        acc_memcpy_to_device_async(&(dev_ptr[j * n]), &(host_copy[j * n]), n * sizeof(real_t), deviceIdx);
#pragma acc wait(deviceIdx)
        for (i = 0; i < n; ++i){
            if (fabs(host_copy[prev_j * n + i] + host_copy[j * n + i] - dev_ptr[prev_j * n + i + (j - prev_j) * n]) > PRECISION * host_copy[prev_j * n + i]){
                err += 1;
            }
        }
        prev_j = j;
    }
    return err;
}
#endif

#ifndef T2
//T2:runtime,construct-independent,async,wait-acc-deps,devonly,devCtrls,memMapAsync,V:2.7-6
//NOTE: The magnitude of real number addition errors is 10 to the log of T2_DEFAULT_TIMES at 2
//NOTE: The precision of device copies is compared using T2_DIFF_THRESHOLD
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"
#define T2_DEFAULT_TIMES 2048

int test2(real_t *dev_ptr, long long int *host_ptr, int deviceIdx){
  int n_errs = 0;
  long long int a;
  int async_q_size = acc_get_num_queues(deviceIdx, acc_get_device_type(deviceIdx));
  real_t *host_matrix = (real_t *)malloc(n * sizeof(real_t) * async_q_size);
  real_t *tmp;
  int num_q_copy_mods = (T2_DEFAULT_TIMES / async_q_size) + 1;

  #pragma acc enter data copyin(host_ptr[0:n])

  for (a = 1; a <= num_q_copy_mods; ++a){
    for (int q_id = 0; q_id < async_q_size; ++q_id){
      if (a * async_q_size - q_id - 1 < num_q_copy_mods * async_q_size - T2_DEFAULT_TIMES){
        for (int x = n - 1; x >= 0; --x){
          host_matrix[(n * q_id) + x] = (a * async_q_size - q_id - 1) * T2_DEFAULT_TIMES * n + x;
        }
        acc_memcpy_to_device_async(&dev_ptr[n * T2_DEFAULT_TIMES * a - (T2_DEFAULT_TIMES * q_id + 1) * n],
          &(host_matrix[(n * q_id)]), sizeof(real_t) * n, deviceIdx);
      }
    }
  }

  for (int q_id = 0; q_id < async_q_size; ++q_id){
    const int cp_width = (T2_DEFAULT_TIMES / async_q_size + (q_id < (T2_DEFAULT_TIMES - (T2_DEFAULT_TIMES / async_q_size) * async_q_size))) * n;
    tmp = (real_t *)malloc(cp_width * sizeof(real_t));
    for (int byte_test = 1; byte_test < sizeof(real_t); ++byte_test){
      #pragma acc parallel async deviceptr(dev_ptr)
      {
        #pragma acc loop seq
        for (int x = 0; x < cp_width; ++x){
          tmp[x] = dev_ptr[(n * T2_DEFAULT_TIMES - 1) - (T2_DEFAULT_TIMES / async_q_size + 1) * q_id * n - x];
        }
      }
      #pragma acc wait
      for (int x = 0; x < cp_width; ++x){
        real_t error_bound = (real_t)(T2_DEFAULT_TIMES / async_q_size + 1) * cbrt(cp_width) * PRECISION;
        if (tmp[x] - (((int)((tmp[x]) / (cp_width * 10))) * (cp_width * 10)) >= 0){
          if (tmp[x] > (error_bound + 1) * cp_width || tmp[x] < (1 - error_bound) * cp_width){
            ++n_errs;
            if (n_errs < 10){
              printf("Error:tmp[x] = %f\n", (double)tmp[x]);
            }
          }
        }
        else{
          if (tmp[x] > (error_bound + 2) * cp_width || tmp[x] < (2 - error_bound) * cp_width){
            ++n_errs;
            if (n_errs < 10){
              printf("Error:tmp[x] = %f\n", (double)tmp[x]);
            }
          }
        }
      }
    }
    free(tmp);
  }
  return n_errs;
}
#endif

int main(){
    int t, device_idx;
    int failcode = 0;
    int failed;
#ifndef T2
    real_t *dev_ptr;
#endif
#ifndef T1
    long long int *host_ptr;
#endif

    int failed_on_device;
    real_t *dev_pointer;
#ifndef T2
    long long int *host_pointer;
#endif
    failed_on_device = 0;
    device_idx = acc_get_device_num(acc_get_device_type(failed_on_device));
#ifndef T2
    dev_pointer = (real_t *)acc_malloc(10 * n * sizeof(real_t));
    host_pointer = (long long int *)malloc(10 * n * sizeof(long long int));
    for (int x = 0; x < 10 * n; ++x){
        host_pointer[x] = 1;
    }
    acc_memcpy_to_device(dev_pointer, host_pointer, 10 * n * sizeof(real_t));
#endif

    for (t = 0; t < NUM_TEST_CALLS; ++t){
#ifndef T2
        failed = 0;
        #pragma acc parallel num_gangs(1) present(dev_pointer[0:10*n])
        {
            #pragma acc loop vector
            for (int x = 0; x < 10 * n; ++x){
                dev_pointer[x] = 1;
            }
        }
        failed = failed + test1(dev_pointer, device_idx, host_pointer);
        failed = failed + test1(NULL, device_idx, host_pointer);
        failed = failed + test1(dev_pointer, device_idx, NULL);
        if (failed != 0){
            failed_on_device += 1;
            device_idx = acc_get_device_num(acc_get_device_type(failed_on_device));
            failed = 0;
            for (int x = 0; x < 10 * n; ++x){
                host_pointer[x] = 1;
            }
            acc_memcpy_to_device(dev_pointer, host_pointer, 10 * n * sizeof(real_t));
            failed = failed + test1(dev_pointer, device_idx, host_pointer);
            failed = failed + test1(NULL, device_idx, host_pointer);
            failed = failed + test1(dev_pointer, device_idx, NULL);
            if (failed != 0){
                failcode = 1;
            }
        }
#endif
#ifndef T1
        failed = 0;
        failed = failed + test2(dev_pointer, host_pointer, device_idx);
        failed = failed + test2(NULL, host_pointer, device_idx);
        failed = failed + test2(dev_pointer, NULL, device_idx);
        if (failed != 0){
            failcode = 1;
        }
        failed_on_device += 1;
        device_idx = acc_get_device_num(acc_get_device_type(failed_on_device));
        failed = 0;
        for (int x = 0; x < 10 * n; ++x){
            host_pointer[x] = 1;
        }
        acc_memcpy_to_device(dev_pointer, host_pointer, 10 * n * sizeof(real_t));
        failed = failed + test2(dev_pointer, host_pointer, device_idx);
        failed = failed + test2(NULL, host_pointer, device_idx);
        failed = failed + test2(dev_pointer, NULL, device_idx);
        if (failed != 0){
            failcode = 1;
        }
#endif
    }

#ifndef T2
    acc_free(dev_pointer, 10 * n * sizeof(real_t));
    free(host_pointer);
#endif

    if (failcode){
        return 1;
    }
    else{
        return 0;