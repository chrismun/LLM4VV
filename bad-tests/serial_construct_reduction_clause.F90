! OpenACC reduction clause compiler implementation test in Fortran
MODULE test

    USE OPENACC
    IMPLICIT NONE

    INTEGER :: n = 1000, errors = 0
    INTEGER, DIMENSION(:), ALLOCATABLE :: arr
    INTEGER :: result_serial = 0, result_parallel = 0
    
CONTAINS

    SUBROUTINE init_array()
      INTEGER :: i
      ALLOCATE(arr(n))
      DO i=1, n
        arr(i) = i
      END DO
    END SUBROUTINE init_array

    SUBROUTINE test_serial_reduction()
      INTEGER :: i
      result_serial = 0
      DO i = 1, n
        result_serial = result_serial + arr(i)
      END DO
    END SUBROUTINE test_serial_reduction
    
    SUBROUTINE test_parallel_reduction()
        INTEGER :: i
        result_parallel = 0
        !$ACC PARALLEL LOOP REDUCTION(+:result_parallel)
        DO i = 1, n
          result_parallel = result_parallel + arr(i)
        END DO
        !$ACC END PARALLEL LOOP
    END SUBROUTINE test_parallel_reduction
    
    SUBROUTINE evaluate_result()
        IF (result_serial .NE. result_parallel) THEN
            errors = errors + 1
        END IF
    END SUBROUTINE evaluate_result
    
    FUNCTION test() RESULT(errors)
        CALL init_array()
        CALL test_serial_reduction()
        CALL test_parallel_reduction()
        CALL evaluate_result()
        RETURN
    END FUNCTION test
    
END MODULE test

PROGRAM main
    USE test
    PRINT*, "Errors in reduction functionality: ", test()
END PROGRAM main