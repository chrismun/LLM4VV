#ifndef T1
!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        !local variables
	      REAL(2),DIMENSION(LOOPCOUNT):: a, b
	      INTEGER:: x, y, C

	      a = 0
	      b = pi
	      C = 0

        acc_copyin(C)
        !$acc data copyout(C) copyin(a(:LOOPCOUNT)) 
        !$acc parallel
        !$acc loop
	      DO x = 1, LOOPCOUNT 
		      C = C + x
	      END DO
	      !$acc end parallel
        !$acc end data
        acc_copyout(C)
        DO x = 1, LOOPCOUNT
          IF(abs(C-x-b(x+1))) > PRECISION THEN
            errors += 1
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