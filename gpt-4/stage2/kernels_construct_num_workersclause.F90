#ifndef T1
!T1:kernels construct num_workersclause,V:2.7-2.3
! Compiler test suite
    LOGICAL FUNCTION test1()
    USE OPENACC
    IMPLICIT NONE
    INCLUDE "acc_testsuite.Fh"

    REAL, DIMENSION(:), ALLOCATABLE :: x, y
    INTEGER :: num_workers, n, i, errors
    REAL rand1, expected_result, result
    
    ! Initialize Arrays
    n = 1024
    ALLOCATE(x(n))
    ALLOCATE(y(n))

    DO i = 1, n
        x(i) = RAND(rand1) * 20.0 - 10.0
        y(i) = 0.0
    END DO
    
    num_workers = 32   ! Set num_workers
    !$ACC Kernels Num_Workers(num_workers)
    DO i = 1, n
        y(i) = ABS(x(i))
    END DO
    !$ACC End Kernels
    
    errors = 0
    expected_result = 0.0
    DO i = 1, n
        expected_result = ABS(x(i))
        IF(y(i) .NE. expected_result) THEN
            errors = errors + 1
        END IF
    END DO
    
    DEALLOCATE(x)
    DEALLOCATE(y)
    
    IF (errors .EQ. 0) THEN
        test1 = .TRUE.   ! No errors, return true
    ELSE
        test1 = .FALSE.   ! Errors encountered, return false
    END IF
    END FUNCTION test1
#endif