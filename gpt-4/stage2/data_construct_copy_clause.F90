!Fortran Code with OpenACC to test Compiler Capability
MODULE ACC_TESTSUITE
  
  CONTAINS 

  INTEGER FUNCTION test1()
    USE OPENACC
    IMPLICIT NONE
    INTEGER, DIMENSION(:), ALLOCATABLE :: a, b
    INTEGER :: size, i, errors 

    size = 1024
    errors = 0
    ALLOCATE(a(size), b(size))

    !$acc data copyin(a(size)) copy(b(size))

    DO i = 1, size
       a(i) = i
       b(i) = 0
    END DO

    !$acc kernels
    DO i = 1, size
       a(i) = a(i) + 1
       b(i) = a(i)
    END DO
    !$acc end kernels
    
   !$acc update host(b(size))

   DO i = 1, size
      IF (b(i) /= i + 1) THEN
         errors = errors + 1
      END IF
   END DO

    !$acc end data

    DEALLOCATE(a, b)
    
    IF (errors == 0) THEN
      test1 = 0
    ELSE
      test1 = 1
    END IF
  END FUNCTION test1

END MODULE ACC_TESTSUITE
  

PROGRAM main
  USE ACC_TESTSUITE
  IMPLICIT NONE
  INTEGER :: success
  success = test1()

  IF (success == 0) THEN
    PRINT*, "Test Passed: Data construct copy clause is working as expected"
  ELSE
    PRINT*, "Test Failed: Check the implementation of data construct copy clause"
  END IF
END PROGRAM main