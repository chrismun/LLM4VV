!T1:acc create,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, PARAMETER :: N = 1024
        REAL(8) :: a, b, c, d
        INTEGER :: errors = 0
        INTEGER :: x


        SEEDDIM(1) = 1
          SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        a = 0.0
        b = 0.0
        c = 0.0
        d = 0.0
        !$acc enter data create(a, b) copyin(c) create(d(1:N))
/*
Create vector in device memory, in d. Then copy vector in c in device memory.
*/

        !$acc data copyout(c(1:N))
          !$acc parallel present(a, b, d(1:N))
            !$acc loop
            DO x = 1, N
              c(x) = a + b + d(x)
            END DO
          !$acc end parallel
        !$acc end data

/*
Only d should be present here.
*/
        DO x = 1, N
          IF (abs(c(x) - d(x)) .gt. TWO_THIRDS) THEN
            errors = errors +1
          END IF
        END DO
        CALL ACC_DELETE(a)
        CALL ACC_DELETE(b)
        CALL ACC_DELETE(d)
        !$acc exit data delete(c)

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