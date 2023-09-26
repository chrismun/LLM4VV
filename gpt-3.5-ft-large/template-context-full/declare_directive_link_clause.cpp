#include "acc_testsuite.h"
#ifndef T1
declareTile(car.y, car.x) int data[(n_tiles_x + 1) * n_tiles_x / 2 * tile_size - (1 + n_tiles_x) * n_tiles_x / 2 / 2];
declareTile(cache_base) int temp[(1 + n_tiles_x) * n_tiles_x / 2 / 2];

//T1:declare,directive,,link,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int prev = 0;

    for (int x = 0; x < n_tiles_x; ++x) {
        prev += x;
        #pragma acc loop vector(16)
        for (int y = 0; y < tile_size; ++y) {
            data[x * tile_size + y - x * (x + 1)/2] = prev;
            prev += n_tiles_x - y + x;
        }
    }

    #pragma acc data copy(data[0:tile_size * n_tiles_x * (n_tiles_x + 1) / 2 / 2]))
    {
        #pragma acc loop
        for (int x = 0; x < n_tiles_x; ++x) {
            #pragma acc data copyout(temp[0:(1 + n_tiles_x) * n_tiles_x / 2 / 2]])
            {
                #pragma acc loop tile(*, *)
                for (int y = 0; y < n_tiles_x - x; ++y) {
                    #pragma acc loop tile(*)
                    for (int z = 0; z < tile_size; ++z) {
                        temp[y * tile_size + z] = data[x * tile_size + y * tile_size + z - x * (x + 1) / 2];
                    }
                }
                #pragma acc loop tile(*, *)
                for (int y = 0; y < n_tiles_x - x - 1; ++y) {
                    #pragma acc loop tile(*)
                    for (int z = 0; z < tile_size; ++z) {
                        data[x * tile_size + y * tile_size + z - x * (x + 1) / 2] = temp[(y + 1) * tile_size + z];
                    }
                }
            }
        }
    }

    prev = 0;
    for (int x = 0; x < n_tiles_x; ++x) {
        prev += x;
        #pragma acc loop vector(16)
        for (int y = 0; y < tile_size; ++y) {
            if (data[x * tile_size + y - x * (x + 1) / 2] != prev) {
                err += 1;
            }
            prev += n_tiles_x - x - 1;
        }
    }

    return err;
}
#endif

#ifndef T2
declareTile(car.x, car.y) int data[10 * n_tiles_x];
int shared[10:get_shr_int() * n_tiles_x];
#endif

#ifndef T3
//T3:Declare,link,V:2.7-3.3
declare create(test3_1) extra
declare(test3_1) &
for extra in {0; VCOLS - 1}
#endif
#ifndef T4
//T4:Declare,link,V:2.7-3.3
declare create(test4_1) extra,  test4_1, test4_2
declare(test4_1, test4_2) &
for extra in {0; VCOLS - 1}
#endif
#ifndef T5
//T5:Declare,link,V:2.7-3.3
declare create(test5_1) test5_1
declare test5_1
#endif
#ifndef T6
//T6:Declare,link,V:2.7-3.3
declare create(test6_1) test6_1
declare test6_1
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