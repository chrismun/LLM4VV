! This code assumes the OpenACC module and potentially other necessary setup
! has been made available by the test suite's environment.
!T1:host_data construct if_present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        ! Assuming "acc_testsuite.Fh" would typically include necessary macros or functions
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        REAL, DIMENSION(:), ALLOCATABLE :: testArray
        REAL :: deviceValue = 5.0
        REAL :: hostValue = 0.0
        INTEGER :: n = 10
        INTEGER :: i

        ALLOCATE(testArray(n))

        ! Initialize the array with values on the host
        testArray = 1.0

        ! Attempt to copy memory to device (if device available and supports it)
        ! This step simulates a scenario where the array may or may not be present on the device
        !$acc enter data copyin(testArray)

        ! Use host_data with if_present to modify the array only if it's present on the device
        !$acc host_data use_device(testArray) if_present
            hostValue = deviceValue
            DO i = 1, n
                testArray(i) = testArray(i) + hostValue
            END DO
        !$acc end host_data

        ! Check if modification took place to determine if if_present clause worked
        IF (hostValue .NE. deviceValue) THEN
            errors = errors + 1
        END IF

        ! Verify one value to see if changes were applied indicating if_present was indeed used
        IF (testArray(1) .NE. 6.0) THEN
            errors = errors + 1
        END IF

        ! Cleanup
        !$acc exit data delete(testArray)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! Assuming acc_testsuite.Fh provides necessary test environment setup
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