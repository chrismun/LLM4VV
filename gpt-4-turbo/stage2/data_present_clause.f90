! Example simplified Fortran code to test OpenACC's "data present" clause functionality.
PROGRAM test_data_present
  USE OPENACC
  IMPLICIT NONE
  INTEGER :: x
  INTEGER :: errors = 0
  
  ! Allocate and initialize x
  x = 10
  
  ! Create a data region ensuring 'x' is present on the device.
  !$ACC ENTER DATA COPYIN(x)
  
  ! Test the "data present" clause.
  CALL test_data_present_clause(x, errors)
  
  !$ACC EXIT DATA DELETE(x)
  
  IF (errors .eq. 0) THEN
    PRINT *, "Test PASSED"
  ELSE
    PRINT *, "Test FAILED with ", errors, " errors"
  END IF
END PROGRAM test_data_present

SUBROUTINE test_data_present_clause(x, errors)
  USE OPENACC
  IMPLICIT NONE
  INTEGER, INTENT(INOUT) :: x
  INTEGER, INTENT(INOUT) :: errors
  LOGICAL :: is_present
  
  ! Expect x to be present due to prior data region.
  is_present = .FALSE.
  
  !$ACC PARALLEL PRESENT(x)
  !$ACC LOOP INDEPENDENT
  DO i = 1, 1  ! Dummy loop for test.
    ! In an actual application, we would perform meaningful computation here.
    is_present = acc_is_present(x, SIZEOF(x))
  END DO
  !$ACC END PARALLEL
  
  IF (.NOT. is_present) THEN
    errors = errors + 1
  END IF
END SUBROUTINE test_data_present_clause