!T1: loop construct device_type clause, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8) ::d_scalar
        INTEGER :: x
        ! Additional device type clause needed to specify device_type
        !$acc data copy(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) create(c(1:LOOPCOUNT)) device_type(nvidia)
          !$acc parallel loop device_type(nvidia)
          DO x = 1, LOOPCOUNT
            c(x) = a(x) + b(x)
          END DO
          !$acc end parallel loop
        !$acc end data
        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (testLoopConstructHostLoop, SEED, LOOPCOUNT)) .gt. PRECISION) THEN
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