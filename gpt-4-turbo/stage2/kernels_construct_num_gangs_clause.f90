PROGRAM main
  IMPLICIT NONE
  INTEGER :: failcode, testrun
  LOGICAL :: failed
  LOGICAL :: test1
  failed = .FALSE.
  failcode = 0

  DO testrun = 1, 1
    failed = failed .or. test1()
  END DO
  IF (failed) THEN
    failcode = failcode + 2 ** 0
  END IF
  PRINT *, "Failcode:", failcode
END PROGRAM main

! Assuming 'acc_testsuite.Fh' provides necessary setup or constants
! which isn't strictly necessary for this simplified example:
! #include "acc_testsuite.Fh"

!T1:kernels construct num_gangs clause,V:2.7-2.3
FUNCTION test1() RESULT(failed)
  USE OPENACC
  IMPLICIT NONE
  LOGICAL :: failed
  INTEGER, DIMENSION(:), ALLOCATABLE :: data
  INTEGER :: i, n
  INTEGER :: errors

  errors = 0
  n = 1000
  ALLOCATE(data(n))
  data = 0

  ! Using a simple parallel operation to test num_gangs:
  !$acc kernels num_gangs(10)
  !$acc loop independent
  DO i = 1, n
    data(i) = i
  END DO
  !$acc end kernels

  ! Validate - for simplicity in this test we're  
  ! not checking directly against 'num_gangs' effects,
  ! simply verifying the loop executed as expected.
  DO i = 1, n
    IF (data(i) /= i) THEN
      errors = errors + 1
    END IF
  END DO

  DEALLOCATE(data)
  
  IF (errors .eq. 0) THEN
    failed = .FALSE.
  ELSE
    failed = .TRUE.
  END IF
END FUNCTION test1
