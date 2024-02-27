PROGRAM test_openacc_host_data_if
        USE OPENACC
        IMPLICIT NONE
        INTEGER, PARAMETER :: N=10
        INTEGER :: x(N), i
        LOGICAL :: condition
        INTEGER :: expectedValues(N), errors

        ! Initialize arrays and variables
        DO i = 1, N
            x(i) = i
            expectedValues(i) = i
        END DO

        condition = .FALSE.
        errors = 0

        ! Using host_data with a conditional if statement
        !$acc host_data if(condition) use_device(x)
            ! Here, we would typically call a GPU-accelerated function. For simplicity, simulate it:
            IF (condition) THEN
                DO i = 1, N
                    x(i) = x(i) * 2  ! This should not happen as condition is FALSE
                END DO
            END IF
        !$acc end host_data

        ! Check if the array remains unchanged to verify the if clause functionality
        DO i = 1, N
            IF (x(i) /= expectedValues(i)) THEN
                errors = errors + 1
            END IF
        END DO

        ! If there are no errors, the functionality works as expected
        IF (errors == 0) THEN
            PRINT*, "HOST_DATA IF clause test PASSED"
        ELSE
            PRINT*, "HOST_DATA IF clause test FAILED with ", errors, " errors"
        END IF

      END PROGRAM test_openacc_host_data_if