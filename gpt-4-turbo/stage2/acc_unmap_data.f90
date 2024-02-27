! Assuming the acc_testsuite.Fh contains necessary constants,
! macros, or utility function declarations for the test suite.
INCLUDE "acc_testsuite.Fh"

!T1:acc unmap data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(10) :: data_host
        INTEGER :: errors = 0
        INTEGER :: i

        ! Populate data_host with test data
        DO i = 1, 10
          data_host(i) = i
        END DO

        ! Map data_host to device
        !$acc enter data copyin(data_host)

        ! Unmap the data without deallocating it
        CALL acc_unmap_data(data_host)

        ! Attempting to access the data should not result in errors,
        ! but would not reflect any device-side modifications, as it's unmapped.
        ! Here, simply ensure no runtime errors occur due to unmapping.

        IF (errors .eq. 0) THEN
          test1 = .FALSE.   ! In Fortran, .FALSE. usually represents success in a boolean context
        ELSE
          test1 = .TRUE.
        END IF

        ! Cleanup: Even though unmapped, explicit data deallocation is good practice
        !$acc exit data delete(data_host)
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL :: test1
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
      END PROGRAM