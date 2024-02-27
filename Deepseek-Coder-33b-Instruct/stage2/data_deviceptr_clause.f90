!T1:data deviceptr clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(N) :: host_data, device_data

        ! Initialize host data
        DO i = 1, N
          host_data(i) = i
        END DO

        ! Copy data to device
        !$acc data copyin(host_data) copyout(device_data)
        !$acc update device(host_data)

        ! Use device data
        !$acc parallel loop deviceptr(host_data)
        DO i = 1, N
          device_data(i) = host_data(i)
        END DO

        !$acc end data

        ! Check results
        DO i = 1, N
          IF (host_data(i) .ne. device_data(i)) THEN
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