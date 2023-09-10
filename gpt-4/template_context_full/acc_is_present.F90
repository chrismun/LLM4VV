#ifndef T1
!T1:acc is present,V:2.7-2.3
    LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: test_array
        INTEGER :: i

        ALLOCATE(test_array(100))

        WRITE(*,*) "Allocating an array in the device"
        !$ACC ENTER DATA COPYIN(test_array)

        FORALL (i=1:100) test_array(i) = i

        WRITE(*,*) "Checking if array is present in the device"
        IF (.NOT. ACC_IS_PRESENT(test_array)) THEN
            errors = errors + 1
            PRINT *, "Array is not present in the device"
        END IF

        !$ACC EXIT DATA DELETE(test_array)
        DEALLOCATE(test_array)

        IF (errors .eq. 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
    END FUNCTION test1
#endif

PROGRAM main
    IMPLICIT NONE
    INTEGER :: failcode, testrun
    LOGICAL :: failed
    INCLUDE "acc_testsuite.Fh"
#ifndef T1
    LOGICAL :: test1
#endif
    failed = .FALSE.
    failcode = 0
#ifndef T1
    DO testrun = 1, NUM_TEST_CALLS
        failed = failed .or. test1()
    END DO
    IF (failed) THEN
        failcode = failcode + 2 ** 0
        failed = .FALSE.
    END IF
#endif
    CALL EXIT (failcode)
END PROGRAM main