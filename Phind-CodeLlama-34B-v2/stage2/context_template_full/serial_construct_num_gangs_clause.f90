#ifndef T1
!T1:serial construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: num_gangs = 10
        INTEGER :: i
        REAL(8), DIMENSION(10) :: a, b, c

        ! Initialize arrays
        DO i = 1, 10
          a(i) = i
          b(i) = i * 2
        END DO

        !$acc serial num_gangs(num_gangs)
        !$acc loop
        DO i = 1, 10
          c(i) = a(i) + b(i)
        END DO
        !$acc end serial

        ! Verify result
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