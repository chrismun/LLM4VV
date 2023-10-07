#ifndef T1
!T1:kernels construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: a = 10
        INTEGER :: b = 20
        INTEGER :: c = 30
        INTEGER :: d = 40
        INTEGER, DIMENSION(LOOPCOUNT) :: hostArray, hostArray2
        INTEGER, DIMENSION(LOOPCOUNT) :: deviceArray, deviceArray2

        hostArray = 5
        hostArray2 = 10

        !$acc kernels firstprivate(a, b)
          deviceArray = hostArray + a
          deviceArray2 = hostArray2 + b
        !$acc end kernels

        DO i = 1, LOOPCOUNT
          IF (deviceArray(i) .ne. (hostArray(i) + a)) THEN
            errors = errors + 1
          END IF
          IF (deviceArray2(i) .ne. (hostArray2(i) + b)) THEN
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