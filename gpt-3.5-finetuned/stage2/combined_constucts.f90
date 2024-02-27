!T1:combined constucts,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0

        INTEGER :: x
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        LOGICAL,DIMENSION(1) :: devtest
        INTEGER :: mult = 1
        devtest(1) = .TRUE.
        !$acc enter data copyin(devtest(1:1))
        !$acc parallel loop
        DO x = 1, LOOPCOUNT
          devtest(x) = .FALSE.
        END DO

        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc parallel loop present(a(1:LOOPCOUNT)) present(b(1:LOOPCOUNT)) present(c(1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          c(x) = c(x) + a(x) + b(x)
        END DO

        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
            errors = errors + 1
            print *, c(x), a(x), b(x)
          END IF
        END DO

        c = 0

        !$acc enter data copyin(c(1:LOOPCOUNT))
        !$acc parallel loop present(a(1:LOOPCOUNT)) present(b(1:LOOPCOUNT)) present(c(1:LOOPCOUNT))
        DO x = 1, LOOPCOUNT
          c(x) = c(x) + a(x) + b(x)
        END DO
        !$acc exit data copyout(c(1:LOOPCOUNT))

        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
            errors = errors + 1
            print *, c(x), a(x), b(x)
          END IF
        END DO

        !$acc exit data delete(c(1:LOOPCOUNT))
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