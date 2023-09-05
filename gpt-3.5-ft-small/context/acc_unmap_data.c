#ifndef T1
//T1:runtime/data,devonly,executable-data,construct-independent,V:2.7-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc host_data use_device(a)
    {
         unsigned int x = 0;
         while (x != 10){
              for (unsigned int y = 1; y < 10; ++y){
                   *((real_t *)a + x * 10 + y) = *((real_t *)a + x * 10) + x + y;
              }
              ++x;
          }
     }
    #pragma acc exit data delete(a[0:n])
    #pragma acc exit data detach(a[90:n-90], a[80:n-80], a[70:n-70], a[60:n-60], a[50:n-50], a[40:n-40], a[30:n-30], a[20:n-20], a[10:n-10], a[0:n-0])
    
    for (int x = 0; x < n; ++x){
        if (fabs(a[x]) > (1e-11 * (fabs(((real_t)((((x % 10) * (x % 10)) / 2) * 10)))) + 3 * PRECISION)){
            err += 1;
        }
    }
    
     return err;
}
#endif

#ifndef T2
//T2:runtime/data,devonly,executable-data,construct-independent,V:2.7-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int *hard_failure = (int *)malloc(sizeof(int));
    int *loop_failed = (int *)malloc(sizeof(int));

    #pragma acc enter data copyin(hard_failure, loop_failed)
    #pragma acc host_data use_device(hard_failure, loop_failed)
    {
         *hard_failure = 0;
         for (unsigned int x = 1; x < 10; ++x){
              #pragma acc loop seq
              for (unsigned int y = 1; y < 10; ++y){
                   if (*((int *)hard_failure) == 0){
                        *loop_failed = 0;
                        for (unsigned int z = 1; z < 10; ++z){
                             if (*((int *)loop_failed) == 0){
                                  unsigned long  int temp = x * y * z;
                                  int *k_pointer = (int *) malloc(temp * sizeof(int));
                                  if (k_pointer != NULL){
                                       for (unsigned int k = 0; k < temp; ++k){
                                            k_pointer[k] = temp - 1;
                                       }
                                       for (unsigned int k = 1; k < temp; ++k){
                                            k_pointer[k] += k_pointer[k - 1];
                                       }
                                       if (k_pointer[temp - 1] != (temp * (temp - 1)) / 2){
                                            *loop_failed = 1;
                                       }
                                       free(k_pointer);
                                  }
                                  else{
                                       *hard_failure = 1;
                                       break;
                                  }
                             }
                        }
                   }
              }
         }
     }
    #pragma acc exit data delete(hard_failure, loop_failed)
    #pragma acc exit data detach(hard_failure, loop_failed)
    
    if (hard_failure[0] == 0){
        err += (loop_failed[0] != 0);
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}