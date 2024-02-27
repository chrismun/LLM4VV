! Example code to test the OpenACC loop construct seq clause
! Make sure to compile with OpenACC support enabled in your Fortran compiler

! Mock include for standardizing the testsuite environment (replace with actual path or content)
INCLUDE "acc_testsuite.Fh"

! Function to test the OpenACC loop construct seq clause
! It returns .FALSE. if the test passes (no errors), .TRUE. otherwise
LOGICAL FUNCTION test1()
  USE OPENACC
  IMPLICIT NONE
  INTEGER :: i
  REAL :: A(100), B(100)
  REAL :: sum
  INTEGER :: errors
  
  errors = 0
  sum = 0.0
  
  ! Initialize arrays
  A = 1.0
  B = 2.0
  
  ! Apply the seq clause to ensure sequential execution
  !$acc parallel loop seq
  DO i = 1, 100
    A(i) = A(i) + B(i)
  END DO
  !$acc end parallel loop
  
  ! Verify the computation was done sequentially
  DO i = 1, 100
    IF (A(i) /= 3.0) THEN
      errors = errors + 1
    END IF
  END DO
  
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
END PROGRAM main