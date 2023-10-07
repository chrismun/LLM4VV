! Include the necessary header file
#include "acc_testsuite.Fh"

! Declare a logical function to test the functionality of the "self" clause
LOGICAL FUNCTION test1()
  USE OPENACC
  IMPLICIT NONE
  
  INTEGER :: a, b
  INTEGER :: errors = 0
  a = 5
  b = 0
    
  !$acc serial self(a == 5)
    b = a
  !$acc end serial
    
  IF (b .ne. a) THEN
    errors = errors + 1
  END IF  

  IF (errors .eq. 0) THEN
    test1 = .FALSE.
  ELSE
    test1 = .TRUE.
  END IF
END FUNCTION test1

PROGRAM main
  IMPLICIT NONE
  INTEGER :: failcode, testrun
  LOGICAL :: failed, test1_output
  INCLUDE "acc_testsuite.Fh"
  
  failed = .FALSE.
  failcode = 0

  DO testrun = 1, NUM_TEST_CALLS
    test1_output = test1() 
    failed = failed .or. test1_output
  END DO
  
  IF (failed) THEN
    failcode = failcode + 2 ** 0
    failed = .FALSE.
  END IF

  CALL EXIT(failcode)
END PROGRAM main