MODULE mod_globals
  INTEGER :: global_var = 0
END MODULE mod_globals

! This declaration is needed for OpenACC
USE OPENACC
! Include the global variable module
USE mod_globals
IMPLICIT NONE

! Test function to verify declare directive's link clause
LOGICAL FUNCTION test_declare_link_clause()
  INTEGER :: local_var
  INTEGER :: errors = 0
  
  ! Set the device data for global_var using the declare directive with link clause
  !$ACC DECLARE LINK(global_var)
  
  ! Create a data region on the device for global_var and modify it
  !$ACC ENTER DATA COPYIN(global_var)
  !$ACC PARALLEL LOOP
  DO local_var = 1, 1
    global_var = 5
  END DO
  !$ACC EXIT DATA COPYOUT(global_var)
  
  ! Check if the modification is reflected on the host
  IF (global_var /= 5) THEN
    errors = errors + 1
  END IF
  
  ! Test passes if there are no errors
  IF (errors == 0) THEN
    test_declare_link_clause = .TRUE.
  ELSE
    test_declare_link_clause = .FALSE.
  END IF
END FUNCTION test_declare_link_clause

PROGRAM main
  USE OPENACC
  USE mod_globals
  IMPLICIT NONE
  LOGICAL :: test_result
  
  ! Run the test for the declare directive's link clause
  test_result = test_declare_link_clause()
  
  IF (test_result) THEN
    PRINT *, "Test for 'declare directive link clause' passed."
    CALL EXIT(0)
  ELSE
    PRINT *, "Test for 'declare directive link clause' failed."
    CALL EXIT(1)
  END IF
END PROGRAM main