#include<openacc.h>
#include<assert.h>
#include<stdlib.h>

#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    // sequece memory 
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));
    float * c = (float *)malloc(n * sizeof(float));
    // test shared memory envolve syndicate data between openacc and host side.
    #pragma acc enter data create(a[0:n],b[0:n],c[0:n])
    // verify the hostptr
    assert(acc_get_deviceptr(a) == acc_hostptr(a));
    assert(acc_get_deviceptr(b) == acc_hostptr(b));
    assert(acc_get_deviceptr(c) == acc_hostptr(c));
    // syndicating the date from host to device
    #pragma acc loop hostptr(a,b,c)
    for (int x = 0; x < n; ++x){
        a[x] = 1;
	b = 1;
	c = 0;
    }
    #pragma acc  loop vector(128) 
    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }
    #pragma acc wait
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 2.0) > 4*PRECISION){
            err += 1;
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