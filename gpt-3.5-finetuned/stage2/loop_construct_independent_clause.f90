!T1:loop construct independent clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8) :: d, devv, ha
        INTEGER :: device = 0
        INTEGER :: x

        SEEDDIM(1) = 1
          SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        ha = 0
        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT))
          !$acc parallel loop independent
          DO x = 1, LOOPCOUNT
            c(x) = a(x) + b(x)
          END DO
        !$acc end data
        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO


        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
          !$acc parallel loop independent reduction(+:ha)
          DO x = 1, LOOPCOUNT
            ha = ha + a(x) + b(x)
          END DO
        !$acc end data
        DO x = 1, LOOPCOUNT
          c(x) = a(x) + b(x)
        END DO
        d = 0
        DO x = 1, LOOPCOUNT
          d = d + c(x)
        END DO
        IF (ABS(d-ha) .gt. 4*PRECISION) THEN
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