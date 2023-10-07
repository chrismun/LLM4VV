#ifndef T1
!T1:async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c, d, e


        !Initilization on HOST
        SEED(2) =  SEED(3)
        CALL RANDOM_SEED(PUT=SEED)

        !Initilization on Device
        !$acc data create(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1: LOOPCOUNT), d(1:LOOPCOUNT), e(1:LOOPCOUNT)) 
            
            !$acc parallel 
                !$acc loop 
             DO i = 1, LOOPCOUNT    
                  a(i) = (0.5 - real(i)/LOOPCOUNT)
                  b(i) = 1
                  c(i) = 2
                  d(i) = 3
             END DO 
            !$acc end parallel
             
            DO_ASYNC(LOOPCOUNT, device_num)
                    
          }   
          END DO
        END DO
        !$acc end data

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