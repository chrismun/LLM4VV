int * vector, int length, int value){
    for (int x = 0; x < length; ++x){
        if (vector[x] == value){
            return true;
        }
    }
    return false;
}

#ifdef TEST_OCL
#include "opencl_utils.h"
#endif

#define present_or_create create

int test_acc_create_create()
{
    bool err = false;

    srand(SEED);

    int devnum = acc_get_device_num(acc_get_device_type());

    int * a = (int *)malloc(30 * sizeof(int));
    int * b = (int *)malloc(30 * sizeof(int));
    int * c = (int *)malloc(30 * sizeof(int));

    for (int x = 0; x < 30; ++x){
        a[x] = rand() % 10;
    }

    #pragma acc data create(b[0:30]), copy(c[0:30])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 30; ++x){
                b[x] = -1;
            }

            #pragma acc loop
            for (int x = 1; x < 29; ++x){
                c[x] = a[x-1] + a[x] + a[x+1];
            }
        }

        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 30; ++x){
                int private_y = -1;
                #pragma acc loop seq
                for (int y = 0; y < 30; ++y){
                    if (is_possible(a, 30, y) && !is_possible(b, 30, y)){
                        private_y = y;
                        #pragma acc loop seq
                        for (int z = 0; z < 30; ++z){
                            if (z == 0 && y < 20){
                                b[z] = y;
                            }
                            if (b[z] == -1 && z > 0 && b[z-1] != -1){
                                b[z] = y;
                            }
                            if (z == 29 && y >= 20 && b[29] == -1){
                                b[29] = y;
                                break;
                            }
                            if (b[z] == private_y){
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    for (int x = 0; x < 30; ++x){
        if (!is_possible(c, 28, c[x])){
            err = true;
        }
    }
    #pragma acc data referencde(b[0:30])
    {
      #pragma acc enter data copyin(b [0: 30])
      #pragma acc parallel
      {
      #pragma acc loop
      for(int x = 0; x < 15; x++)
          c[x] = b[x] + a[x];
      }
      #pragma acc exit data  delete(b[0:30])
      #pragma acc parallel
      {
      #pragma acc loop
      for(int x = 15; x < 30; x++)
          c[x] = b[x] + a[x];
      }
    }
 

    for (int x = 0; x < 30; ++x){
        if (c[x] != 2 * a[x]){
            err = true;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    int deviceid = acc_get_device_num(acc_get_device_type());
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_create_create();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}