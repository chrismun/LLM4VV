! Include necessary OpenACC module
MODULE acc_module
  USE OPENACC
  IMPLICIT NONE
END MODULE acc_module

!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test_acc_update_device()
        USE acc_module
        IMPLICIT NONE
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(1) :: host_array
        
        ! Initialize the array on the host
        host_array(1) = 10
        
        ! Ensure the array is present on the device
        !$acc enter data copyin(host_array)
        
        ! Modify the value on the host
        host_array(1) = 20
        
        ! Update the modified value to the device
        !$acc update device(host_array)
        
        ! Modify the value on the device
        !$acc parallel loop
        DO i = 1, SIZE(host_array)
          host_array(i) = host_array(i) + 10
        END DO
        !$acc end parallel loop
        
        ! Update the modified value back to the host to verify
        !$acc update self(host_array)
        
        ! Checking if the device value was correctly updated and then modified
        IF (host_array(1) /= 30) THEN
          errors = errors + 1
        END IF
        
        !$acc exit data delete(host_array)

        IF (errors .eq. 0) THEN
          test_acc_update_device = .FALSE.
        ELSE
          test_acc_update_device = .TRUE.
        END IF
      END FUNCTION test_acc_update_device

      PROGRAM main
        USE acc_module
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test_acc_update_device
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test_acc_update_device()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        PRINT *, "Test completed with failcode", failcode
        CALL EXIT (failcode)
      END PROGRAM main