!T1:acc attach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(N) :: a, b, c
        REAL(8) :: d
        INTEGER :: i

        SEEDDIM([SEEDS])

        ! Initializing
        !$acc enter data create(a(1:N), b(1:N), c(1:N))

        ! Generate random data for a, b and initialize c
        CALL RANDOM_SEED(PUT=SEED)
        CALL RANDOM_NUMBER(a)
        !$acc data copyin(a(1:N), b(1:N)) create(c(1:N))
        !$acc parallel
        !$acc loop
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel
        !$acc end data
        !$acc enter data create(d(1:1))
        !$acc data copyin(c(1:N), a(1:N)) copyout(b(1:N))
        !$acc parallel
        !$acc loop
        DO i = 1, N
          c(i) = c(i) + a(i)
        END DO
        !$acc end parallel

        !$acc exit data copyout(c(1:N)) attach(c(1:N))
        !$acc enter data copyin(c(1:N))

        DO i = 1, N
          IF (abs(c(i) - (3 * a(i)))) .gt. PRECISION THEN
            errors = errors + 1
          END IF
        END DO
        !$acc exit data delete(c(1:N))
        
        !$acc exit data copyout(a(1:N), b(1:N))) detach(n(1:N))

        !$acc exit data delete(a(1:N), b(1:N))
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