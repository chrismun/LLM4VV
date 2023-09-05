#include "acc_testsuite.h"
void test_context() {
    /* Test executing async on the device with different async ids which are 0 */
    int err = 0, async_correction_0 = 0;
    int* a;
    int async_id;

    if (faulty_two_argument(&async_correction_0) == -1){
        err = 1;
        goto async_exit_1;
    }

    a = (int *)malloc(n * sizeof(int));
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel async
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 0;
            }
        }
    }
    #pragma acc exit data delete(a[0:n]) async(async_correction_0)
    for (async_id = 0; async_id <= async_correction_0; ++async_id){
        #pragma acc wait async(async_id)
    }
    for (int x = 0; x < n; ++x){
        if (a[x] != 0){
            err = 1;
            break;
        }
    }

    for (async_id = async_correction_0; async_id >= 0; --async_id){
        if (a[7] != 0){
            err = 1;
        }
        if (async_id != async_correction_0){
            #pragma acc wait async(async_id+1)
        }
        if (async_id != 0){
            #pragma acc exit data delete(a[34:n]) async(async_id-1)
        }
    }
    for (int x = 0; x < 7; ++x){
        if (a[x] != 0){
            err = 1;
        }
    }
    if (err == 1){
        err = 0;
        for (int x = 0; x < n; ++x){
            a[x] = 2;
        }
        for (int x = 0; x < n; ++x){
            a[x] = 0;
        }
        #pragma acc enter data copyin(a[0:n]) async
        #pragma acc parallel async
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 1;
            }
        }
        #pragma acc exit data delete(a[0:n]) async
        for (async_id = 0; async_id <= 0; ++async_id){
            #pragma acc wait async(async_id)
        }
        for (int x = 0; x < n; ++x){
            if (a[x] != 1){
                err = 1;
                break;
            }
        }
    }
    #pragma acc enter data delete(a[0:n])
    if (err != 0){
        err = 0;
        for (int x = 0; x < n; ++x){
            a[x] = 2;
        }
        #pragma acc data copyin(a[0:n])
        {
            #pragma acc parallel async(async_correction_0)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = 1;
                }
            }
            #pragma acc parallel async(async_correction_0)
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] += 1;
                }
            }
        }

        for (async_id = 0; async_id <= async_correction_0; ++async_id){
            #pragma acc wait async(async_id)
        }
        for (int x = 0; x < n; ++x){
            if (a[x] != 3){
                err = 1;
                break;
            }
        }
    }

    /* Test entering with async value */
    int async_id_corrections[5];
    async_id_corrections[0] = 3;
    async_id_corrections[1] = 5;
    async_id_corrections[2] = 19;
    async_id_corrections[3] = 1;
    async_id_corrections[4] = 0;
    for (int x = 0; x < 5; ++x){
        for (int y = 0; y < n; ++y){
            a[y] = 0;
        }
        #pragma acc data copyin(a[0:n]) async(async_id_corrections[x])
        {
            #pragma acc parallel async(async_id_corrections[x])
            {
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    a[y] = 1;
                }
            }
        }
        #pragma acc exit data delete(a[0:n]) async(async_id_corrections[x])
        for (async_id = 0; async_id <= async_id_corrections[x]; ++async_id){
            #pragma acc wait async(async_id)
        }
        for (int y = 0; y < 7; ++y){
            if (a[y] != 1){
                err = 1;
            }
        }
        for (int y = 7; y < 16; ++y){
            if (a[y] != 0){
                err = 1;
            }
        }
        for (int y = 16; y < 34; ++y){
            if (a[y] != 1){
                err = 1;
            }
        }
        for (int y = 34; y < n; ++y){
            if (a[y] != 0){
                err = 1;
            }
        }

        for (async_id = async_id_corrections[x]; async_id >= 0; --async_id){
            #pragma acc enter data delete(a[34:n]) async(async_id)
            if (a[7] != 1){
                err = 1;
            }
            #pragma acc wait async(async_id)
        }
        for (int y = 0; y < 7; ++y){
            if (a[y] != 0){
                err = 1;
            }
        }
    }

    async_exit_1:
    free(a);
    return;
}

int main(){
    srand(1);
    test_context();
    test_memory();
    test_profiling();
    return 0;