!T1:declare directive device_resident clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT), DEVICE_RESIDENT :: a, b
        REAL(8), DIMENSION(LOOPCOUNT) :: c
        INTEGER i

        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        ! complete test here

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)

        !$acc declare create(a(1:LOOPCOUNT), b(1:LOOPCOUNT))

        !$acc parallel loop reduction(+:errors)
        DO i = 1, LOOPCOUNT
          a(i) = a(i) + c(i)
          b(i) = a(i) + c(i)
          c(i) = a(i) + b(i)
        END DO

        !$acc end parallel loop

        DO i = 1, LOOPCOUNT
          IF (abs(a(i) - (c(i) / 2)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(b(i) - (c(i) / 2)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
          IF (abs(c(i) - (a(i) + b(i))) .gt. PRECISION) THEN
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