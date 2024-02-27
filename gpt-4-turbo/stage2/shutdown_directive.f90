! Verify OpenACC shutdown directive implementation
! Using acc_init and acc_shutdown to demonstrate the effect
! Assumes acc_testsuite.Fh is available and included for common test suite utilities

MODULE test_module
  USE OPENACC
  IMPLICIT NONE

CONTAINS

  LOGICAL FUNCTION test_shutdown_directive()
    INTEGER :: device_id
    LOGICAL :: shutdown_success
    INTEGER :: errors
    
    errors = 0
    shutdown_success = .FALSE.
    
    ! Initialize a device to ensure an active device session
    device_id = acc_get_device_num(acc_get_device_type())
    IF (device_id .GE. 0) THEN
      CALL acc_init(acc_get_device_type())
      
      ! Attempt to shut down the device and free resources
      !$acc shutdown
      
      ! Following the shutdown, attempt to use the device and check for errors
      ! This part simplifies the check, assuming an error would occur if the shutdown was unsuccessful
      CALL acc_set_device_num(device_id, acc_get_device_type())
      IF (acc_get_device_num(acc_get_device_type()) .EQ. device_id) THEN
        errors = errors + 1
      END IF
      
      ! If errors remain 0, it suggests shutdown was successful
      shutdown_success = (errors .EQ. 0)
    ELSE
      ! If no device was found to init, mark test as failed
      shutdown_success = .FALSE.
    END IF
    
    test_shutdown_directive = shutdown_success
  END FUNCTION test_shutdown_directive
  
END MODULE test_module

PROGRAM main
  USE test_module
  IMPLICIT NONE
  LOGICAL :: failed
  INTEGER :: failcode
  
  failed = .FALSE.
  failcode = 0
  
  ! Since this test suite is simplified, it directly calls the test function
  failed = .NOT. test_shutdown_directive()
  
  IF (failed) THEN
    failcode = failcode + 1
  END IF
  
  CALL EXIT(failcode)
END PROGRAM main