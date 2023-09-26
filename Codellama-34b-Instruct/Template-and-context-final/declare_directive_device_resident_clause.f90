fortran
#ifndef T1
!T1:declare directive device_resident clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL, DIMENSION(10) :: a, b, c
        REAL, DIMENSION(10) :: d, e, f
        COMMON /my_common/ a, b, c
        COMMON /my_common/ d, e, f
        
        !$acc declare device_resident(a, b, c)
        !$acc declare device_resident(d, e, f)
        
        !$acc parallel
        !$acc loop
        DO i = 1, 10
          a(i) = b(i) + c(i)
          d(i) = e(i) + f(i)
        END DO
        !$acc end parallel
        
        !$acc end declare
        
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