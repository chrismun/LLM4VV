#ifndef T1
!T1:data construct copy clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, ALLOCATABLE, DEVICE :: a(:)
        
        
        ALLOCATE(a(n))
            
        !$acc data copy(a(0:n))
            !$acc parallel
                a(1) = 1
            !$acc end parallel
        !$acc end data
        DO testrun = 1, NUM_TEST_CALLS
            IF ((a(1) .eq. 0)) THEN
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