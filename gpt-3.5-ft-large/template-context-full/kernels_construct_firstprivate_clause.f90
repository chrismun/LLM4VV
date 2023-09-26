#ifndef T1
!T1:kernels construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(KIND=8),DIMENSION(10)::a, b
        REAL(KIND=8):: c


        !$acc data copy(a(1:10)) 
          c = 1
          !$acc kernels firstprivate(c)
          !$acc loop 
          DO test = 1, 600
		
            !$acc loop independent
            DO i = 1, 10
            c = 1
              a(i) = a(i) + c
            END DO
            
          END DO    
          !$acc end kernels

        !$acc end data

        DO i = 1, 10
          x = x + a(i)
        END DO
        IF x .eq. 0 THEN 
          errors = errors + 1
        ENDIF

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