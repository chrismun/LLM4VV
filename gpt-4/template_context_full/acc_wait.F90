! T1:acc_wait, V:2.7-2.3
MODULE acc_test_module
    USE OPENACC
    IMPLICIT NONE
END MODULE acc_test_module

PROGRAM test_acc_wait
    USE OPENACC
    USE acc_test_module
    IMPLICIT NONE

    REAL, DIMENSION(:), ALLOCATABLE, DEVICE :: darr
    INTEGER :: i, async_id
    INTEGER :: failcode, testrun
    LOGICAL :: failed = .FALSE.
    INTEGER :: errors = 0
    INTEGER, PARAMETER :: array_size = 1000000

    ALLOCATE(darr(array_size))
    async_id = acc_async_test

    !$acc enter data copyin(darr)
    !$acc parallel loop async(async_id)
    FOR i = 1, array_size
        darr(i) = i
    END DO

    CALL acc_wait(async_id)
    !$acc exit data copyout(darr)
  
    ! Checking if the data was processed correctly
    FOR i = 1, array_size
        IF (darr(i) /= i) THEN
            errors = errors + 1
        END IF
    END DO

    IF (errors > 0) THEN
        failed = .TRUE.
        WRITE (*,*) "Test failed with ", errors, " errors"
    ELSE
        WRITE (*,*) "Test passed"
    END IF

    DEALLOCATE(darr)

    IF (failed) THEN
        failcode = failcode + 2 ** 0
    END IF

    CALL EXIT (failcode)
END PROGRAM test_acc_wait