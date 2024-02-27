!T1:host_data construct if_present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, a_host

        ALLOCATE(a(N), a_host(N))

        ! Initialize data on the host
        DO i = 1, N
          a_host(i) = i
        END DO

        ! Copy data to the device
        !$acc data copyin(a_host) copyout(a)

        ! Update data on the device
        !$acc host_data use_device(a)
        !$acc parallel loop present(a)
        DO i = 1, N
          a(i) = a_host(i) * 2
        END DO
        !$acc end host_data

        !$acc end data

        ! Check the results
        DO i = 1, N
          IF (a(i) /= a_host(i) * 2) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, a_host)

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