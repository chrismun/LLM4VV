#ifndef T1
!T1:cache directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, a_copy, b, b_copy, c
        INTEGER :: x

        x = 1
        SEEDDIM(1) = 1
        #pragma acc cache(SEEDDIM, acc_create: a(0:LOOPCOUNT)), copyin(a(0:LOOPCOUNT)))
        DO WHILE (x .lt. SEED)
          x = x + 1
        END DO
        a_copy = (FSIZE(16) * acos(-1) + 1) * x

        x = 1
        SEEDDIM(1) = 1
        #pragma acc cache(SEEDDIM, acc_create: b(0:LOOPCOUNT)), copyin(b(0:LOOPCOUNT)))
        DO WHILE (x .lt. SEED)
          x = x + 1
        END DO
        b_copy = (FSIZE(16) / acos(-1)) * x

        #pragma acc data copyout(c(0:LOOPCOUNT)) present(a(0:LOOPCOUNT), b(0:LOOPCOUNT)))
        #pragma acc kernels loop
        DO I = 0, LOOPCOUNT
          c(I) = a(I) + b(I)
        END DO

        DO I = 0, LOOPCOUNT
          IF (abs(c(I) - (a_copy(I) + b_copy(I))) .gt. 1) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM