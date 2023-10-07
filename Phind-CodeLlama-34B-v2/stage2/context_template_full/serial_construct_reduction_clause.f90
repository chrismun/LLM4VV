#ifndef T1
!T1:serial construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j, k
        REAL(8) :: a(10), b(10), c(10), d(10)
        REAL(8) :: sum_a, sum_b, sum_c, sum_d

        DO i = 1, 10
          a(i) = i
          b(i) = i * 2
          c(i) = i * 3
          d(i) = i * 4
        END DO

        !$acc serial
        !$acc loop reduction(+:sum_a)
        DO i = 1, 10
          sum_a = sum_a + a(i)
        END DO
        !$acc end serial

        !$acc serial
        !$acc loop reduction(*:sum_b)
        DO i = 1, 10
          sum_b = sum_b * b(i)
        END DO
        !$acc end serial

        !$acc serial
        !$acc loop reduction(max:sum_c)
        DO i = 1, 10
          sum_c = MAX(sum_c, c(i))
        END DO
        !$acc end serial

        !$acc serial
        !$acc loop reduction(min:sum_d)
        DO i = 1, 10
          sum_d = MIN(sum_d, d(i))
        END DO
        !$acc end serial

        IF (sum_a .NE. 55 .OR. sum_b .NE. 38416 .OR. sum_c .NE. 30 .OR. sum_d .NE. 1) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END If
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