! Including necessary modules and libraries

! Defining the test for OpenACC serial construct if clause
!T1:serial construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        ! Including the testsuite header for utilities
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x_host, x_device
        INTEGER, PARAMETER :: threshold = 5
        INTEGER :: value
        
        ! Initialize data
        x_host = 10
        x_device = 0
        
        ! Test "if" clause effectiveness by setting "value" to trigger the OpenACC condition
        value = 6
        
        !$acc serial copyout(x_device) if(value > threshold)
            x_device = x_host
        !$acc end serial
        
        IF (x_device /= x_host) THEN
          errors = errors + 1
        END IF
        
        ! Reset and run with "if" condition not met
        x_device = 0
        value = 4
        
        !$acc serial copyout(x_device) if(value > threshold)
            x_device = x_host
        !$acc end serial
        
        ! If x_device is modified, it means the serial region was incorrectly entered
        IF (x_device == x_host) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

! The main program to run the test1 function
      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! Include the testsuite header
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
        CALL EXIT(failcode)
      END PROGRAM