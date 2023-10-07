#ifndef T1
!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(LOOPCOUNT):: a, a_host
        INTEGER:: x
        
        !host variable separate 
        a = 0
        a_host = 0
        
        SEEDDIM(1) = 1
        #if REAL_IS_DOUBLE
              SEEDDIM(2) = 7823
        #else
              SEEDDIM(2) = 17823
        #endif
        DO x = 1, LOOPCOUNT
              a_host(x) = rand(SEEDDIM) 
        END DO

        acc_copyin(a(1:LOOPCOUNT ))
        
        !$acc update device(a(1:LOOPCOUNT))
        
        DO x = 1, LOOPCOUNT
          IF(a(x) - a_host(x).gt. PRECISION)THEN
            errors = errors + 1
          END IF
        END DO
        !$acc end distribute 
        !$acc exit data delete(a(1:LOOPCOUNT ) )

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