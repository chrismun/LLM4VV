fortran
#ifndef T1
!T1:loop construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x = 0
        INTEGER :: y = 0
        INTEGER :: z = 0
        INTEGER :: i
        
        !$acc parallel copy(x) reduction(+:x,y)
        !$acc loop worker reduction(+:x,z)
        DO i = 1, 10
          x = x + 1
          z = z + 2
        END DO
        !$acc end parallel
        
        IF (x .ne. 10) THEN
          errors = errors + 1
        END IF
        
        IF (y .ne. 0) THEN
          errors = errors + 1
        END IF
        
        IF (z .ne. 20) THEN
          errors = errors + 1
        END IF
        
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