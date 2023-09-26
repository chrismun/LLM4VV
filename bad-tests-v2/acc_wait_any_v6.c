#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <openacc.h>

#define N 100000

void sleep_ms(int milliseconds) {
  usleep(milliseconds * 1000);
}
 
int test_acc_wait_any(int *a, int *b, int *c, int *d) {
  int i, failures = 0;

  #pragma acc parallel copyin(a[0:N], b[0:N]) copyout(c[0:N]) present(d[0:N])
  {
    #pragma acc loop
    for (i = 0; i < N; i++) {
      c[i] = a[i] + b[i];
    }
  }

  #pragma acc parallel copyin(c[0:N]) async
  {
    #pragma acc loop
    for (i = 0; i < N; i++) {
      d[i] = c[i] * c[i];
    }
  }
  
  for (i = 0; i < N; i++) {
    if (d[i] != (a[i]+ b[i]) * (a[i]+b[i])) {
      failures++;
    }
  }

  return failures;
}

#define NUM_TESTS 10

int main() {
  int a[N], b[N], c[N], d[N];
  int successes = 0;

  srand(time(NULL));
  
  for (int i = 0; i < N; i++) {
    a[i] = rand()%10;
    b[i] = rand()%10;
  }

  for (int t = 0; t < NUM_TESTS; t++) {
    int failure = test_acc_wait_any(a, b, c, d);
    if (failure == 0) {
      successes++;
    }
    sleep_ms(1000);
  }

  printf("Successes: %d\n", successes);
  printf("Failures: %d\n", NUM_TESTS - successes);
  
  return 0;
}