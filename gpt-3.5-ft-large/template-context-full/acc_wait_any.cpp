#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
	int err = 0;
	size_t err_count = 0, kind;
	int* a = (int *)malloc(n * sizeof(int));
	int* b = (int *)malloc(n * sizeof(int));
	int* c = (int *)malloc(n * sizeof(int));
	int * host_w = (int *)malloc(3 * sizeof(int));
	host_w[0] = acc_create_unordered(0, t1, n);
        host_w[1] = acc_create_unordered(0, t2, n);
        host_w[2] = acc_create_unordered(0, t3, n);
	# pragma acc data copyin(host_w[0:3])
	{
        # pragma acc data create(a[0:n], b[0:n], c[0:n])
        {
                # pragma acc parallel loop async (1)
                for (int x = 0; x < n; ++x){
                        a[x] = 5;
                }
                # pragma acc parallel loop async (2)
                for (int x = 0; x < n; ++x){
                        b[x] = 7;
                }
                # pragma acc parallel loop async (3)
                for (int x = 0; x < n; ++x){
                        c[x] = 11;
                }
                # pragma acc wait
                kind = acc_get_device_type();
                for (int x = 0; x < n; ++x){
                        if (dev_test[1] && a[x] + b[x] != c[x]){
                                err_count = err_count + 1;
                        }
                        if (dev_test[1] &&  acc_get_device_num(kind) - 1 > -1){
                                err_count = err_count + 1;
                        }
                }
                # pragma acc wait any
                for (int x = 0; x < n; ++x){
                        if (dev_test[1] && a[x] ! = 5){
                                err_count = err_count + 1;
                        }
                }
        }
        for (int x = 0; x < n; ++x){
                if (dev_test[1] && (a[x] != 5 && err_count != 0 || ( a[x] + b[x] != c[x] && err_count != 0)) {
                        err_count = err_count + 1;
                }
        }
	}
	free(host_w);

    return err;
}
#endif

#ifndef T2
//T2: acc wait any,V:2.7-3.3
int test2(){
	int err = 0;
	size_t err_count = 0, kind;
        int* a = (int *)malloc(n * sizeof(int));
        int* b = (int *)malloc(n * sizeof(int));
        int* c = (int *)malloc(n * sizeof(int));
        int* w = (int *)malloc(2048 * sizeof(int));
        int* base = (int *)malloc(2048 * sizeof(int));
        host_w = (int *)malloc(1 * sizeof(int));
        int dev_num = acc_get_device_num(acc_get_device_type());
        int w_index;

        for (int x = 0; x < n; ++x){
        	a[x] = 0;
	}
        for (int x = 0; x < n; ++x){
                b[x] = 1;
        }
        for (int x = 0; x < n; ++x){
                b[x] = 2;
        }
        for (int x = 0; x < 2048; ++x){
                base[x] = 3;
        }
        for (int x = 0; x < 2048; ++x){
                w[x] = 0;
        }
        # pragma acc data copyin(a[0:n], b[0:n], c[0:n],  base[0:2048])
        {
                while (count < 13){
                        # pragma acc parallel loop
                        for (int x = 0; x < n; ++x){
                                a[x] = a[x] + 1;
                        }
                        for (int x = 0; x < 4; ++x){
                                c_test[x] = 0;
                        }
                        for (int x = 0; x < 2048; ++x){
                                if (c[x] < 14){
                                        c_test[x%4] += a[x] + b[x];
                                }
                                else {
                                        c_test[x%4] = 0;
                                }
                        }
                        for (int x = 0; x < 4; ++x){
                                if (c_test[x] != 3){
                                        err_count += 1;
                                }
                        }
                        c_test[0] = (c_test[0]/3);
                        if (err_count != 0){
                                return 1;
                        }
                        # pragma acc parallel loop async (catch)
                        for (int x = 0; x < 2048; ++x){
                                c[x] = a[x] + b[x];
                        }
                        # pragma acc wait any
                        for (int x = 0; x < 2048; ++x){
                                if (c[x] == 10){
                                        while (c[x] == 10){
                                                x = x;
                                        }
                                        err_count = err_count + 1;
                                }
                        }
                }
        }
        for (int x = 0; x < n; ++x){
                w_index = (a[x] - 1) * 67108864 + b[x] * 8192;
                if (w[w_index] == 0){
                        w[w_index] = 1;
                } else {
                        err_count += 1;
                }
        }

        for (int x = 0; x < 2048; ++x){
                for (int y = 0; y < 16; ++y){
                        w_index = x * 32 + y;
                        if (base[x] == 3){
                                if (w[w_index] != 1){
                                        err_count += 1;
                                }
                        } else {
                                if (w[w_index] != 0){
                                        err_count += 1;
                                }
                        }
                }
        }

        free(a);
        free(b);
        free(c);
        free(w);
        free(base);
        if (err_count == 0){
                err = err + 1;
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