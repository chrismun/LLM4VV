MODULE testsuite
    USE openacc
    IMPLICIT NONE
    
    INTEGER, PARAMETER :: N = 100
    INTEGER :: i
    INTEGER, DIMENSION(N) :: array
    
    CONTAINS
    
    LOGICAL FUNCTION test_num_gangs()
        INTEGER :: computed_gangs
        
        array(:) = 0

        !$ACC KERNELS NUM_GANGS(10)
            DO i = 1, N
                array(i) = array(i) + 1
            END DO
        !$ACC END KERNELS
        
        computed_gangs = sum(array)
        
        IF (computed_gangs .eq. N) THEN
            test_num_gangs = .TRUE.
            PRINT *, "Test Passed."
        ELSE
            test_num_gangs = .FALSE.
            PRINT *, "Test Failed."
        ENDIF
    END FUNCTION test_num_gangs
END MODULE testsuite

PROGRAM test
    USE testsuite
    INTEGER :: result
    
    result = test_num_gangs()
    
    IF (.NOT. result) THEN
        PRINT *, "ERROR: OpenACC TEST - KERNELS NUM_GANGS FAILED"
    ENDIF
END PROGRAM test