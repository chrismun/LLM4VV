!T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Initialize data

        integer, parameter :: N = 1024
        real(8), dimension(N) :: a, b, c, d
        integer :: x
        
        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        d = 0

        !$acc data copyin(a(1:N), b(1:N)) create(c(1:N)) copyout(d(1:N))
          !$acc parallel
            !$do
            DO x = 1, N
              c(x) = a(x) + b(x)
            END DO
          !$acc end parallel
          CALL acc_memcpy_from_device(d(1), c(1), N*8)
        !$acc end data

        DO x = 1, 0
          IF (abs(d(1) - (a(1) + b(1))) .gt. PRECISION) THEN
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