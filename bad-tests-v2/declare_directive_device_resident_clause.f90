#ifndef T1
!T1:declare directive device_resident clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), ALLOCATABLE, DEVICE_RESIDENT :: a(:)
        INTEGER :: n = 1000

        ALLOCATE(a(n))
        a = 1.0

        !$acc parallel loop device_resident(a)
        DO i = 1, n
          a(i) = a(i) + 1.0
        END DO
        !$acc end parallel loop

        DO i = 1, n
          IF (a(i) .ne. 2.0) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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