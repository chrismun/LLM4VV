#include "acc_testsuite.h"
#ifndef T1
	//T1: host_data, use_device, V:2.7-3.3
	int test1(){
		int err = 0;
		srand(SEED);
        int test = 1;
        int device = 1;
        int copied = 2;
        real_t * host_vec = (real_t *)malloc(n * sizeof(real_t));
        real_t* device_vec = (real_t *)malloc(n * sizeof(real_t));

        for (int x = 0; x < n; ++x){
			host_vec[x] = rand() / (real_t)(RAND_MAX / 10);
		}

        #pragma acc enter data copyin(host_vec[0:1])
        
		#pragma acc data copyout(host_vec[0:1]) present(host_vec[0:1])
        {
            #pragma acc host_data use_device(host_vec[0:1])
            {
                // host_vec += 1 -> host_vec[]+1 is highly unordered
                device_vec[0] = host_vec[0] + 1;
                #pragma acc enter data copyin(device_vec[0:1])
                #pragma acc kernels present(device_vec[0:1])
                {
                    device_vec[0] = host_vec[0];
                }
            }
            #pragma acc host_data use_device(host_vec[0:1])
            {
                #pragma acc exit data delete(host_vec[0:1]) copyout(host_vec[0:1])
            }
        }

        if (fabs(host_vec[0] - device_vec[0]) > PRECISION){
            err = 1;
        }

        free(host_vec);
        free(device_vec);

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