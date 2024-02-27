#include "acc_testsuite.h"
#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

	int device = acc_get_device_type();
	if (device != acc_device_none){
		cudaStream_t host_data_detach_stream;
		int *a = (int *)malloc(n * sizeof(int));
		int *b = (int *)malloc(n * sizeof(int));
		int *c = (int *)malloc(n * sizeof(int));
		#pragma acc data copy(a[0:n], b[0:n]) copyin(c[0:n]) detach(c[0:n])
		{
			for (int x = 0; x < n; ++x){
				a[x] = rand() % 10;
				b[x] = 2 * rand() % 10;
				c[x] = 0;
			}
			#pragma acc parallel loop
			for (int x = 0; x < n; ++x){
				c[x] = a[x] + b[x];
			}
			#pragma acc enter data create(c[0:n]) on_device(device) detach(c[0:n]) // results in an Autocreated inline data region with finalize(detach(c[0:n]))
			#pragma acc parallel loop present(c[0:n])
			for (int x = 0; x < n; ++x){
				c[x] += c[x];
			}
			#pragma acc exit data copyout(c[0:n]) delete(a[0:n], b[0:n]) // Autocreated inline data region with finalize(detach(c[0:n])) generates an exit data directive
			for (int x = 0; x < n; ++x){
				//c[x] refers to the original pointer  below, host function equation c[z] makes use of the detached value
				if (c[x] != ((a[x] + b[x]) * 2)){
					err += 1;
				}
			}
		}
		free(a);
		free(b);
		free(c);
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