!file: test_acc_copyin.f90
MODULE testmod
    USE OPENACC
    IMPLICIT NONE
    CONTAINS

    LOGICAL FUNCTION test_acc_copyin()
        INTEGER :: host_var
        INTEGER, ALLOCATABLE :: deviceArray(:)
        INTEGER :: errors = 0

        host_var = 10
        ALLOCATE(deviceArray(1))

        !$acc enter data copyin(host_var)
        !$acc parallel loop copyin(host_var)
        DO i = 1, 1
            deviceArray(i) = host_var + 1
        END DO
        !$acc exit data copyout(deviceArray)
        
        IF (deviceArray(1) /= 11) THEN
            errors = errors + 1
        END IF

        DEALLOCATE(deviceArray)

        IF (errors == 0) THEN
            test_acc_copyin = .FALSE.
        ELSE
            test_acc_copyin = .TRUE.
        END IF
    END FUNCTION test_acc_copyin
END MODULE testmod

PROGRAM verify_acc_copyin
    USE testmod
    IMPLICIT NONE
    INTEGER :: failcode, testrun
    LOGICAL :: failed
    LOGICAL :: testoutcome
    INTEGER, PARAMETER :: NUM_TEST_CALLS = 1

    failed = .FALSE.
    failcode = 0

    DO testrun = 1, NUM_TEST_CALLS
        testoutcome = test_acc_copyin()
        failed = failed .OR. testoutcome
    END DO

    IF (failed) THEN
        failcode = failcode + 2 ** 0
    END IF
    
    PRINT *, "Test Outcome: ", failed
    STOP failcode

END PROGRAM verify_acc_copyin