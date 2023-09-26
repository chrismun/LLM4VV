#ifndef T1
!T1:acc memcpy d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: devNum, errors = 0
        INTEGER, DIMENSION(10) :: srcArray, destArray
        INTEGER(KIND=8) :: srcPtr, destPtr, bytes = 40 ! 40 bytes is equivalent to 10 Integer elements.
   
        DO devNum = 1, acc_get_num_devices(acc_device_default)
            CALL acc_set_device_num(devNum, acc_device_default)
            CALL acc_memcpy_d2d(destPtr, srcPtr, bytes, devNum, devNum)
        
            IF (ALL(destArray == srcArray)) THEN
                errors = errors + 1
                PRINT *, "Error on device ", devNum
            END IF
        END DO
         
        ! Checking error condition
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
    failcode = 0
#ifndef T1
    DO testrun = 1, NUM_TEST_CALLS
      failed = failed .or. test1()
    END DO
    IF (failed) THEN
      failcode = failcode + 2 ** 0
    END IF
#endif
    CALL EXIT (failcode)
END PROGRAM main