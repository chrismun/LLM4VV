!T1:kernels construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        
        INTEGER :: i, errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER :: d
        
        !$acc kernels loop default(none)
        DO i = 1, LOOPCOUNT
          c(i) = a(i) + b(i) * i
        END DO

        DO i = 1, LOOPCOUNT
          IF (abs(c(i) - (a(i) + b(i) * i)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

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