#ifndef T1
!T1:enter data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(10) :: a, b, c

        !$acc enter data copyin(a(1:10), b(1:10))
        a = 1.0
        b = 2.0
        !$acc enter data create(c(1:10))
        c = 0.0

        !$acc parallel
        !$acc loop
        DO i = 1, 10
          c(i) = a(i) + b(i)
        END DO
        !$acc end parallel

        !$acc exit data delete(c(1:10))

        DO i = 1, 10
          IF (c(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

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