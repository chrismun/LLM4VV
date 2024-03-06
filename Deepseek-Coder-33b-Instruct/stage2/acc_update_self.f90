!T1:acc update self,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(N) :: a, b
        INTEGER :: i

        ! Initialize array
        DO i = 1, N
          a(i) = REAL(i)
        END DO

        ! Copy array to device
        !$acc data copyin(a) copyout(b)

        ! Update array on device
        !$acc update device(a)

        ! Update array on host
        !$acc update self(a)

        !$acc end data

        ! Check if array was updated correctly
        DO i = 1, N
          IF (a(i) .ne. REAL(i)) THEN
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