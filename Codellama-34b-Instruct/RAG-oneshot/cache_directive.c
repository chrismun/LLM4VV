#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 100
#define M 100

int main() {
    int i, j, k;
    int a[N][M];
    int b[N][M];

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            a[i][j] = i * j;
            b[i][j] = 0;
        }
    }

    // Use the cache directive to fetch array elements into the highest level of the cache
    #pragma acc cache(a[0:N][0:M])
    {
        // Perform some operations on the arrays
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                b[i][j] = a[i][j] + 1;
            }
        }
    }

    // Check the results
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (b[i][j] != a[i][j] + 1) {
                printf("Error: b[%d][%d] = %d, expected %d\n", i, j, b[i][j], a[i][j] + 1);
            }
        }
    }

    return 0;
}