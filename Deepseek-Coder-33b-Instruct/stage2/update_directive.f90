!T1:update directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(N) :: a, a_host

        ! Initialize host arrays
        DO i = 1, N
          a_host(i) = i
        END DO

        ! Copy data to device
        !$acc data copyin(a_host) copyout(a)

        !$acc parallel loop
        DO i = 1, N
          a(i) = a_host(i)
        END DO

        ! Update device data with host data
        !$acc update device(a)

        !$acc end data

        ! Check the results
        DO i = 1, N
          IF (a(i) /= a_host(i)) THEN
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