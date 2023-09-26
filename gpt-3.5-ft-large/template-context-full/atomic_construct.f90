#ifndef T1
!T1:atomic construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(2),DIMENSION(5):: a, b                
        REAL(2):: temp
        INTEGER:: x, y 
               

        !Initialise the vectors
        SEEDDIM(1) = 1
#       SEED
        CALL RANDOM_SEED(PUT=SEED)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)

        !$acc data copy(a(1:5),b(1:5))
          !$acc parallel
            !$acc loop
            DO x=1, 5
              temp = b(x)
              !$acc atomic write
               a(x) = temp
            END DO
          !$acc end parallel
        !$acc end data
        
        DO y = 1, 5
          DO x = 1, y
            IF close(a(y),b(y),.1) THEN
              errors = errors + 1 
            END IF
          END DO
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