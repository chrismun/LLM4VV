#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int ishost;
	int *host = (int *)malloc(n * sizeof(int));
	int *test = (int *)malloc(n * sizeof(int));
	int *a = (int *)malloc(n * sizeof(int));
	int *b = (int *)malloc(n * sizeof(int));
	for (int x = 0; x < iterations; ++x){
    	for (int y = 0; y < n; ++y){
        	a[y] = 1;
        	b[y] = 1;
    	}
    	#pragma acc data copyin(a[0:n]) create(test[0:n]) copyout(b[0:n])
    	{
        	#pragma acc parallel
        	{
            	test[0] = 0;
            	#pragma acc loop
            	for (int k = 0; k < n; ++k){
                	#pragma acc atomic
                	*(test + k) = *(test + k) + 1;
            	}
            	#pragma acc loop
            	for (int k = 0; k < n; ++k){
                	b[k] = a[k] + test[k];
            	}
        	}
        	for (int y = 0; y < n; ++y){
            		host[y] = 1 + a[y];
        	}
        	if (comp_vectors(host, b, n, 0) < 2){
            	err += 1;
        	}
    	}
	}
#endif
    return failcode;
}