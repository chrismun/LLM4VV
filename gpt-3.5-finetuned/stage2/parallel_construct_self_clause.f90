!T1:parallel construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: i
        REAL(8),DIMENSION(LOOPCOUNT,10):: a, b, c, dat

        INTEGER :: errors = 0

        dat = 0
        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data copyin(a(1:LOOPCOUNT,1:10), b(1:LOOPCOUNT,1:10)) create(c(1:LOOPCOUNT,1:10))
        !$acc parallel present(a(1:LOOPCOUNT,1:10), b(1:LOOPCOUNT,1:10), c(1:LOOPCOUNT,1:10))
          !$acc loop
          DO i = 1, LOOPCOUNT
            c(i, 1:10) = c(i, 1:10) + a(i, 1:10) + b(i, 1:10)
          END DO
        !$acc end parallel

        !$acc exit data copyout(c(1:LOOPCOUNT,1:10)) delete(a(1:LOOPCOUNT,1:10), b(1:LOOPCOUNT,1:10))

        !$omp parallel do private(i) reduction(+:errors)
        DO i = 1, LOOPCOUNT
          errors = errors + DOT_PRODUCT(c(i, 1:10), c(i, 1:10)) - 400
        END DO
        !$omp end parallel do

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