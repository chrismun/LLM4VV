! Assert the requirement for OpenACC support
!$acc routine
      MODULE openacc_test_utilities
        INTERFACE
          FUNCTION acc_get_property(dev_num, dev_type, property) BIND(C, NAME="acc_get_property")
            USE ISO_C_BINDING
            INTEGER(C_INT), VALUE :: dev_num
            INTEGER(C_INT), VALUE :: dev_type
            INTEGER(C_INT), VALUE :: property
            INTEGER(C_SIZE_T) :: acc_get_property
          END FUNCTION
        END INTERFACE
      END MODULE

      PROGRAM main
        USE openacc_test_utilities
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INTEGER, PARAMETER :: NUM_TEST_CALLS = 1
        
        failed = .FALSE.
        failcode = 0
        
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        
        CALL EXIT(failcode)
      END PROGRAM main

      LOGICAL FUNCTION test1()
        USE openacc_test_utilities
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER(C_SIZE_T) :: device_memory
        
        ! Fetch the total device memory for the current device.
        device_memory = acc_get_property(0, acc_device_not_host, acc_property_memory)
        
        ! Verify we got a valid memory size
        IF (device_memory == 0) THEN
          errors = errors + 1
        END IF

        IF (errors .EQ. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1