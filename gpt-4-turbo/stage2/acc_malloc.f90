! This code is designed to test the OpenACC implementation of acc_malloc in Fortran.
! It tries to allocate memory on the device and checks if the allocation was successful.

! Define T1 to avoid double inclusion
!T1:acc malloc,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE ISO_C_BINDING
        USE OPENACC
        IMPLICIT NONE
        
        ! Including a hypothetical header for the testsuite utilities
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER(C_SIZE_T) :: bytes
        TYPE(C_PTR) :: devPtr
        INTEGER :: errors = 0
        
        ! Size in bytes to allocate
        bytes = 1024_C_SIZE_T

        ! Allocate memory on the device
        devPtr = acc_malloc(bytes)
        
        ! Check for allocation failure
        IF (C_ASSOCIATED(devPtr)) THEN
          ! Allocation successful
          PRINT*, "Allocation successful."
        ELSE
          ! Allocation failed or bytes was zero
          PRINT*, "Allocation failed or bytes was zero."
          errors = errors + 1
        END IF
        
        ! Free the allocated memory
        CALL acc_free(devPtr)
        
        ! Return the status
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

PROGRAM main
        USE OPENACC
        IMPLICIT NONE

        ! Assume acc_testsuite.Fh provides the necessary environment setup and constants
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        EXTERNAL :: test1
        failed = .FALSE.
        failcode = 0
        
        ! Run the acc_malloc test
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          PRINT*, "Test Failed."
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        ELSE
          PRINT*, "Test Passed."
        END IF
        ! Exit the program signalling success or failure
        CALL EXIT(failcode)
END PROGRAM main