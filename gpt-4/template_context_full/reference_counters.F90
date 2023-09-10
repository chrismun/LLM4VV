#ifndef T1
!T1:reference counters,V:2.7-2.5.1
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh" 
        INTEGER :: errors=0
        INTEGER, DIMENSION(:), ALLOCATABLE :: data
        INTEGER :: i

        ALLOCATE(data(5))
        
        data = (/ (i, i=1,5) /)
        
        !$ACC ENTER DATA COPYIN(data)
        !$ACC PARALLEL LOOP PRESENT(data)
        DO i = 1,5
            data(i) = data(i) * 2
        END DO
        IF (acc_get_device_type() == acc_device_gpu) THEN
            IF (acc_is_present(data, SIZE(data)) .eq. .FALSE.) THEN
                errors = errors + 1
            END IF
        END IF
        !$ACC EXIT DATA COPYOUT(data)
        
        IF (acc_get_device_type() == acc_device_gpu) THEN
            IF (acc_is_present(data, SIZE(data))) THEN
                errors = errors + 1 
            END IF 
        END IF
        DEALLOCATE(data) 

        IF (errors .eq. 0) THEN
            test1 = .TRUE.
        ELSE
            test1 = .FALSE.
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