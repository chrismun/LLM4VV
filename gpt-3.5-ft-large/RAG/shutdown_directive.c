#ifndef REAL
#define REAL double
#endif

int main (int argc, char *argv[]) {
    int cpu = 0;
    int errors = 0;

    warns = 0;
    perf = 0;

#if defined(_OPENACC)
    printf("shutdown directive\n");
    for (int x = 0; x < (1 << 10); ++x){
      int _n;
      srand(x);
      _n = (int)(rand() / (double)(RAND_MAX) * 1024);
      if (test_shutdown(_n) == 1){
        errors += 1;
      }
    }
#endif

    return errors;
}