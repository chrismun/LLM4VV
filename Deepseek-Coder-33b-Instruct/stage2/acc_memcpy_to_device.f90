!T1:acc memcpy to device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(N) :: host_array, device_array
        INTEGER :: i

        ! Initialize host array
        DO i = 1, N
          host_array(i) = REAL(i)
        END DO

        ! Copy host array to device
!$ACC DATA COPYIN(host_array) COPYOUT(device_array)
        CALL acc_memcpy_to_device(device_array, host_array, N*4)

        ! Verify the copy
        DO i = 1, N
          IF (host_array(i) .NE. device_array(i)) THEN
            errors = errors + 1
          END IF
        END DO

        !$ACC END DATA

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