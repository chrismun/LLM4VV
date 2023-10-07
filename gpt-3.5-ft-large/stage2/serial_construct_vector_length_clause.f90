#ifndef T1
!T1:serial construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(10*LOOPCOUNT) :: a, b, c
        INTEGER :: x
        
        SEEDDIM(1) = 1
        #ifdef _OPENACCpragma acc serial
        DO x = 1, 10 * LOOPCOUNT
          a(x) = RAND(SEED)
          b(x) = RAND(SEED)
        END DO
        #endif
        #Loop testing can't be done
        #Loop testing can't be done.
        c(1:10*LOOPCOUNT) = a(1:10*LOOPCOUNT) + b(1:10*LOOPCOUNT)
        DO x = 1, 10*LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. 3) THEN
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