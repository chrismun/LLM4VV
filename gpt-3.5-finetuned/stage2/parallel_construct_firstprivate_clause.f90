!T1:parallel construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8) :: a, b, sum = 0
        INTEGER :: x

        a = 1.0
        b = 2.0
        
        !$acc parallel loop firstprivate(a, b, sum)
        DO x = 1, LOOPCOUNT
          sum = sum + a + b + x
        END DO

        DO x = 1, LOOPCOUNT
          sum = sum - x
        END DO

        IF (abs(sum - LOOPCOUNT - 3.0) .gt. PRECISION) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM