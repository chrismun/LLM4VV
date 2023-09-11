#ifndef T1
!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: host_array, device_array
        INTEGER :: i

        ! Initialize host_array
        DO i = 1, 10
          host_array(i) = i
        END DO

        ! Copy host_array to device_array
        CALL acc_copyin(host_array)

        ! Modify host_array
        DO i = 1, 10
          host_array(i) = host_array(i) * 2
        END DO

        ! Update device_array using acc_update_device
        CALL acc_update_device(host_array)

        ! Copy device_array back to host_array
        CALL acc_copyout(device_array, host_array)

        ! Check if device_array matches host_array
        DO i = 1, 10
          IF (device_array(i) .ne. host_array(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM