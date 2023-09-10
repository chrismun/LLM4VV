#ifndef T1
!T1:update directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),TARGET   :: callee(LOOPCOUNT), caller(LOOPCOUNT)
        INTEGER i
        
        for i = 1 to LOOPCOUNT
          callee(i) = (i-1) * 1.0
          caller(i) = (i+1) * 1.0
        end
 
        !$acc enter data copyin(callee(LOOPCOUNT))
        !$acc update  if      (is_present(callee,LOOPCO   UNT))   host(c
        aller(LOOPCOUNT))
        for i = 1 to LOOPCOUNT
          if (abs(callee(i) - calle r(i)) .gt. HOLYCOW) then
            errors = errors + 1
          end
        end
      
        !$acc exit data  delete(callee(LOOPCOUNT))

        IF(errors.eq.0) THEN
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