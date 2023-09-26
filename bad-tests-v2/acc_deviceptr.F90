#ifndef T1
!T1:acc deviceptr,V:2.7-2.3
    LOGICAL FUNCTION test1()
        USE ISO_C_BINDING
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, DIMENSION(:), ALLOCATABLE :: arrayHost       
        TYPE(C_PTR) :: arrayHostPtr, arrayDevicePtr       

        INTEGER :: errors = 0 
        INTEGER :: dataSize = 10   
        INTEGER :: i       
 
        ALLOCATE(arrayHost(dataSize))  

        !$ACC ENTER DATA COPYIN(arrayHost)

        DO i = 1, dataSize
            arrayHost(i) = i
        END DO

        arrayHostPtr = C_LOC(arrayHost(1))
        arrayDevicePtr= ACC_DEVICEPTR(arrayHostPtr)
        
        IF (ARRAYDEVICEPTR == C_NULL_PTR) THEN  
            errors = errors + 1
        END IF

        !$ACC EXIT DATA COPYOUT(arrayHost)

        DEALLOCATE(arrayHost)

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