!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i, host_array(N), device_array(N)

        ! Initialize host array
        DO i = 1, N
          host_array(i) = i
        END DO

        ! Copy host array to device
        !$acc data copyin(host_array) copyout(device_array)

        ! Copy host array to device array
        !$acc parallel loop present(host_array, device_array)
        DO i = 1, N
          device_array(i) = host_array(i)
        END DO

        ! Modify device array
        !$acc parallel loop present(device_array)
        DO i = 1, N
          device_array(i) = device_array(i) * 2
        END DO

        !$acc end data

        ! Copy device array back to host
        !$acc data copyin(device_array) copyout(host_array)

        ! Copy device array to host array
        !$acc parallel loop present(device_array, host_array)
        DO i = 1, N
          host_array(i) = device_array(i)
        END DO

        !$acc end data

        ! Check if host array was updated correctly
        DO i = 1, N
          IF (host_array(i) .ne. i * 2) THEN
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