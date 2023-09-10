#ifndef T1
!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: data_host = (/1, 2, 3, 4, 5, 6, 7, 8, 9, 10/)
        INTEGER, DIMENSION(10) :: data_device
        !$ACC ENTER DATA COPYIN(data_host)
        CALL acc_update_device(data_host, SIZE(data_host)*4)
        
        !$ACC PARALLEL LOOP COPYOUT(data_device)
        DO i = 1, 10
            data_device(i) = data_host(i)
        END DO
        
        !$ACC EXIT DATA COPYOUT(data_host)
        
        DO i = 1, 10
            IF (data_host(i) .NE. data_device(i)) THEN
                errors = errors + 1
            END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END 
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
      END PROGRAM