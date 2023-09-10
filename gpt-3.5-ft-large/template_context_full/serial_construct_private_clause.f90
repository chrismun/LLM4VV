#ifndef T1
!T1:serial construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
	TREAL(8),DIM(0:1),PRIVATE:: x
	x = -1
        !$acc data copyout(isDevice) create(A(0:n),DIM(0:1),pntrs(0:1),DIM(0:1))
          A = 0
          !$acc parallel loop
          DO i = 0, n
            If (i.eq.n) THEN
              value = cos(pi)
            ELSE
              value = cos(i)
            END IF
            !$acc loop worker
            DO j = 0, n
              A(i) = A(i) + exp(value) * exp(value)
            END DO
          END DO
          !$acc end data
          testcase = 1
          DO i = 0, n
            IF (A(i) .lt. 2 * exp(cos(i))) THEN
              errors = errors + 1
              A(i) = 0
            END IF
          END DO
        END DO
        IF (abs(testcase) .lt. PRECISION) THEN
          test1= .FALSE.
        ELSE
          test1 = .TRUE
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        USE OPENACC
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