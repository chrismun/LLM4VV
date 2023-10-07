#ifndef T1
!T1:cache directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b, c

        DO i = 1, 10
          a(i) = i
          b(i) = i * 2
        END DO

!$acc data copy(a(1:10), b(1:10), c(1:10))
!$acc cache(a(1:5), b(1:5))
!$acc parallel loop
        DO i = 1, 10
          c(i) = a(i) + b(i)
        END DO
!$acc end data

        DO i = 1, 10
          IF (c(i) .ne. a(i) + b(i)) THEN
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