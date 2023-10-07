#ifndef T1
!T1:acc update self,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b

        CALL RANDOM_NUMBER(a)
        b = 0

        !$acc enter data copyin(a(:LOOPCOUNT)))
        !$acc update self(a(1:LOOPCOUNT)))
        If (IS_ASYNC) Then
          !$acc kernels async(acc_async_num)
        Else
          !$acc kernels
        End If
          !$acc loop
          DO i = 1, LOOPCOUNT
            a(i) = a(i) * a(i)
          END DO
        End DO
        !$acc update host(a(1:LOOPCOUNT)))
        errors = errors + IS_TRUE(devices_are_equal(LOOPCOUNT, a, b))

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