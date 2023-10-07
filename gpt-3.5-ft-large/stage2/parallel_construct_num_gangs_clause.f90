#ifndef T1
!T1:parallel construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(10, 10) :: a, b, c
        INTEGER :: x, y
        
        SEEDDIM(1) = 1
#if REAL
        REAL SEEDS(5)
        SEEDDIM(0) = 5
#endif
#if DOUBLE
        DOUBLE PRECISION SEEDS(5)
        SEEDDIM(0) = 2
#endif
        CALL RANDOM_SEED(PUT=SEEDS)
        
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        
        !$acc data copyin(a(1:10, 1:10), b(1:10, 1:10)) copyout(c(1:10, 1:10))
          !$acc parallel num_gangs(2, 5)
            !$acc loop gang
            DO y = 1, 2
              !$acc loop worker
              DO x = 1, 10
                c(x, y) = c(x, y) + a(x, y) + b(x, y)
              END DO
            END DO
          !$acc end parallel
        !$acc end data

        DO y = 1, 2
          DO x = 1, 10
            IF (abs(c(x, y) - (a(x, y) + b(x, y))) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
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