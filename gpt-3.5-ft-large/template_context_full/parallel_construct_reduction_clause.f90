#ifndef T1
!T1:parallel construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(21)::a,c
          INTEGER:: x
     
        SEEDDIM(1) = 1
        #ifdef SEED
            SEEDDIM(1) = SEED
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
            a = 0
          b = 0
        CALL RANDOM_NUMBER(c)
        
        !$acc parallel copyin(c(1:21)) copy(a(1:21))
          !$acc loop
          DO x = 1, 21
            a(x) = (b(x) + c(x))
          END DO
        !$acc end parallel
        
        DO x = 1, 21
          IF (abs(a(x) - b(x) - c(x)) .GT. PRECISION) THEN
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