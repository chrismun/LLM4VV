! Include necessary OpenACC module
USE OPENACC
! If `acc_testsuite.Fh` is needed for actual testsuite setup include it,
! otherwise, this example will proceed without it.
! INCLUDE "acc_testsuite.Fh"

!T1:acc_get_device_type,V:2.7-2.3
      LOGICAL FUNCTION test_acc_get_device_type()
        IMPLICIT NONE
        INTEGER(acc_device_kind) :: device_type
        
        ! Initialize test result to FALSE - meaning no errors by default
        test_acc_get_device_type = .FALSE.
        
        ! Retrieve the current device type
        device_type = acc_get_device_type()
        
        ! Check if a valid device type is returned (not acc_device_none)
        IF (device_type == acc_device_none) THEN
          test_acc_get_device_type = .TRUE.
        END IF
        
      END FUNCTION test_acc_get_device_type

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! Note: Assuming `acc_testsuite.Fh` includes definition for NUM_TEST_CALLS
        ! If not, ensure to define it or adjust the loop.
        ! INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test_acc_get_device_type
        failed = .FALSE.
        failcode = 0
        
        ! Perform the test multiple times if needed
        DO testrun = 1, 1 ! Assuming NUM_TEST_CALLS = 1 for this simple test
          failed = failed .OR. test_acc_get_device_type()
        END DO
        IF (failed) THEN
          ! If the test failed, update failcode
          failcode = failcode + 2 ** 0
        END IF
        
        ! Terminate the program with the failcode
        CALL EXIT (failcode)
      END PROGRAM main