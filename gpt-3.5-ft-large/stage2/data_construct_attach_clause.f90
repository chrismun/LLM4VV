#ifndef T1
!T1:data construct attach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: host_array
        REAL(8),DIMENSION(LOOPCOUNT):: host_array2
        REAL(8),DIMENSION(LOOPCOUNT):: host_array3
        REAL(8),DIMENSION(LOOPCOUNT+1):: host_array4
        REAL(8),DIMENSION(LOOPCOUNT+1):: device_array4
        REAL(8),DIMENSION(LOOPCOUNT+1):: host_array5
        REAL(8),DIMENSION(LOOPCOUNT+1):: device_array5
        REAL(8),DIMENSION(LOOPCOUNT*ITERATIONS):: device_array
        REAL(8),DIMENSION(LOOPCOUNT*ITERATIONS):: device_array2
        REAL(8),DIMENSION(LOOPCOUNT*ITERATIONS):: device_array3
        REAL(8),DIMENSION(1):: host_array6
        REAL(8),DIMENSION(1):: device_array6
        INTEGER:: x, y, temp
        INTEGER:: errors
        errors = 0


        !$acc enter data copyin(host_array(1:LOOPCOUNT)), create(device_array(1:LOOPCOUNT)), attach(host_array2(1:LOOPCOUNT)) 
        
        !$acc enter data present_or_attach(host_array3(1:LOOPCOUNT))
        
        DO  WHILE(1)
          temp = 0
          !$acc enter data copyin(host_array4(1:LOOPCOUNT + 1)), create(device_array4(1:LOOPCOUNT + 1)), attach(host_array4(1:LOOPCOUNT)))
          !$acc enter data create(device_array4(LOOPCOUNT + 1:2*LOOPCOUNT)), attach(host_array4(1:LOOPCOUNT + 1)), attach(host_array4(1:LOOPCOUNT)))          
          
          !$acc enter data present_or_attach(host_array5(1:LOOPCOUNT)), present_or_create(device_array5(1:LOOPCOUNT))
          temp = temp + 1
          !$acc enter data copyin(host_array6(1:1)), create(device_array6(1:1)), attach(host_array6(1:1)))
          !$acc data copyout(host_array6(1:1)) present(device_array6(1:1))
            !$acc data copyout(host_array6(1:1)) present(device_array6(1:1))
          !$acc end data
          DO WHILE (temp > 0)
            device_array6(1) = 1
            host_array6(1) = 0
            temp = temp - 1
          END DO
          IF (temp .eq. 1) THEN
            DO y = 1, LOOPCOUNT
              DO x = 1, ITERATIONS
                device_array5(y) = 1
                host_array5(y) = 1
              END DO  
            END DO      
            DO y = 1, LOOPCOUNT + 1
              DO x = 1, ITERATIONS
                device_array4(y) = 1
                host_array4(y) = 1
              END DO  
            END DO      
            DO y = 1, LOOPCOUNT
              DO x = 1, ITERATIONS
                device_array3(y) = 0
              END DO
            END DO
            DO y = 1, LOOPCOUNT
              DO x = 1, ITERATIONS
                device_array2(y) = 0
              END DO
            END DO
            DO y = 1, LOOPCOUNT
              DO x = 1, ITERATIONS
                device_array(y) = 0
              END DO
            END DO
            DO x = 1, LOOPCOUNT
              host_array(x) = 0
              host_array2(x) = 1
              host_array3(x) = 1
            END DO
            EXIT
          END IF
        END DO

		att_count = att_count + 1
        DO y = 1, LOOPCOUNT
          host_array(y) = 1
        END DO
        !$acc update device(host_array(1:LOOPCOUNT))
        DO y = 1, LOOPCOUNT
          IF (abs(host_array2(y)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO
        
        !$acc update device(host_array3(1:LOOPCOUNT))
        DO y = 1, LOOPCOUNT
          IF (abs(host_array3(y) - 1) .gt. PRECISION) THEN
            errors = errors + 10
          END IF
        END DO
        !Put it at the end to prevent double entries
        !$acc exit data copyout(host_array(1:LOOPCOUNT)), copyout(device_array(1:LOOPCOUNT)), detach(host_array2(1:LOOPCOUNT))
        !$acc exit data copyout(host_array3(1:LOOPCOUNT)), delete(device_array2(1:LOOPCOUNT))
        

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